/**
 * @file dcdf.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <functional>
#include <utility>

#include "algorithm/graineval/dcdf.h"
#include "generator/dcdf_generator.h"
#include "logging/log.h"
#include "utils/utils.h"

namespace algorithm {

#define DCDF_ALG_PLUGIN_NAME "algorithm_p600"

boost::log::sources::severity_logger<logging::severity_level> lg_dcdf_ge;
BOOST_LOG_SCOPED_LOGGER_TAG(lg_dcdf_ge, "Module", "DCDF_GE");

typedef boost::shared_ptr<algorithm::graineval_api>(ge_create_t)();

class dcdf_fobs : public generator::dcdf_obs_frame {
 public:
  explicit dcdf_fobs(std::function<void(generator::dcdf_frame)> frame_cb)
      : m_frame_cb(frame_cb) {}

  void handle_frame(generator::dcdf_frame f) override {
    if (m_frame_cb) m_frame_cb(f);
  }

 private:
  std::function<void(generator::dcdf_frame)> m_frame_cb;
};

class dcdf_sobs : public generator::dcdf_obs_status {
 public:
  explicit dcdf_sobs(std::function<void(generator::dcdf_status)> status_cb)
      : m_status_cb(status_cb) {}

  void handle_status(generator::dcdf_status s) override {
    if (m_status_cb) m_status_cb(s);
  }

 private:
  std::function<void(generator::dcdf_status)> m_status_cb;
};

dcdf::dcdf(std::shared_ptr<generator::dcdf_engine> dcdf_engine, std::string dev_id)
    : m_dcdf_engine(dcdf_engine),
    m_dev_id(dev_id),
    m_post_proc(false),
    m_remain_batch(0),
    m_sem_data(0),
    update_sid(true),
    m_ge(nullptr) {
  m_dcdf_fobs = std::make_shared<dcdf_fobs>(
    std::bind(&dcdf::handle_dcdf_frame, this, std::placeholders::_1));
  m_dcdf_sobs = std::make_shared<dcdf_sobs>(
    std::bind(&dcdf::handle_dcdf_status, this, std::placeholders::_1));
  m_run = true;
  m_proc_thread = std::thread(&dcdf::process_entity, this);
}

dcdf::~dcdf() {
  stop();
  m_sres_obs.clear();
  m_run = false;
  m_sem_data.post();
  m_proc_thread.join();
}

int dcdf::scan_plugin(std::string path) {
  if (path.empty()) path = utils::common::instance()->algorithm_plugin_path();
  auto lib_path = boost::dll::fs::path(path) / DCDF_ALG_PLUGIN_NAME;
  try {
    boost::dll::shared_library lib(lib_path, boost::dll::load_mode::append_decorations);
    if (lib.has(GRAINEVAL_CREATOR_SYMBOL)) {
      m_ge = boost::dll::import_alias<ge_create_t>(boost::move(lib), GRAINEVAL_CREATOR_SYMBOL)();
      BOOST_LOG_SEV(lg_dcdf_ge, logging::INFO)
        << "plugin found, name: " << m_ge->name() << ", ver: " << m_ge->version();
    } else {
      BOOST_LOG_SEV(lg_dcdf_ge, logging::MAJOR) << "symbol not found from plugin: " << lib_path;
      return -1;
    }
  } catch (...) {
    // 库文件/库目录不存在
    BOOST_LOG_SEV(lg_dcdf_ge, logging::MAJOR) << "plugin not found";
    return -2;
  }
  return 0;
}

int dcdf::start() {
  if (!m_ge) return -1;
  m_pres = std::unique_ptr<algorithm::result>(new algorithm::result);
  m_dcdf_engine->attach(m_dcdf_fobs);
  m_dcdf_engine->attach(m_dcdf_sobs);
  return 0;
}

int dcdf::stop() {
  m_dcdf_engine->detach(m_dcdf_fobs);
  m_dcdf_engine->detach(m_dcdf_sobs);
  return 0;
}

/**
 * @brief 增加数据观察者
 * 
 * @param obs 
 */
void dcdf::attach(std::shared_ptr<ge_obs_sample_result> obs) {
  for (const auto &it : m_sres_obs) if (it == obs) return;
  m_sres_obs.push_back(obs);
}

/**
 * @brief 删除数据观察者
 * 
 * @param obs 
 */
void dcdf::detach(std::shared_ptr<ge_obs_sample_result> obs) {
  m_sres_obs.remove(obs);
}

/**
 * @brief 增加数据观察者
 * 
 * @param obs 
 */
void dcdf::attach(std::shared_ptr<ge_obs_batch_result> obs) {
  for (const auto &it : m_bres_obs) if (it == obs) return;
  m_bres_obs.push_back(obs);
}

/**
 * @brief 删除数据观察者
 * 
 * @param obs 
 */
void dcdf::detach(std::shared_ptr<ge_obs_batch_result> obs) {
  m_bres_obs.remove(obs);
}

void dcdf::notify_sresults(std::unique_ptr<algorithm::result> pres) {
  algorithm::result res = *pres;
  for (auto& obs : m_sres_obs) {
    obs->sample_result(res);
  }
}

void dcdf::notify_bresults(algorithm::result bres) {
  for (auto& obs : m_bres_obs) {
    obs->batch_result(bres);
  }
}

void dcdf::handle_dcdf_frame(generator::dcdf_frame f) {
  if (update_sid) {
    m_sid = f.sid;
    update_sid = false;
  }
  std::shared_ptr<cv::Mat> pua = std::make_shared<cv::Mat>(
    cv::Mat(f.ua->h, f.ua->w, CV_8UC3, f.ua->data.get()).clone());
  std::shared_ptr<cv::Mat> pub = std::make_shared<cv::Mat>(
    cv::Mat(f.ub->h, f.ub->w, CV_8UC3, f.ub->data.get()).clone());
  std::shared_ptr<cv::Mat> pda = std::make_shared<cv::Mat>(
    cv::Mat(f.da->h, f.da->w, CV_8UC3, f.da->data.get()).clone());
  std::shared_ptr<cv::Mat> pdb = std::make_shared<cv::Mat>(
    cv::Mat(f.db->h, f.db->w, CV_8UC3, f.db->data.get()).clone());
  m_bdata.push({m_dev_id, f.id, f.wei, f.time_str, f.grain_type, f.abnormal_type,
    {pua, pub, pda, pdb}});
  m_sem_data.post();
}

void dcdf::handle_dcdf_status(generator::dcdf_status s) {
  switch (s) {
    case generator::dcdf_status::sample_done:
    BOOST_LOG_SEV(lg_dcdf_ge, logging::INFO) << "sample done, waiting for post process";
    m_post_proc = true;
    m_sem_data.post();
    break;

    case generator::dcdf_status::batch_done:
    m_remain_batch++;
    BOOST_LOG_SEV(lg_dcdf_ge, logging::INFO) << "batch done, remain batch: " << m_remain_batch;
    break;

    case generator::dcdf_status::engine_off:
    break;

    case generator::dcdf_status::engine_on:
    break;
    default:break;
  }
}

void dcdf::process_entity() {
  while (true) {
    m_sem_data.wait();
    if (!m_run) break;
    if (!m_bdata.empty()) {
      // 从数据池中取数据
      algorithm::batch_data data = m_bdata.front();
      m_bdata.pop();

      // 算法处理
      m_ge->process(data, m_pres.get());
      m_remain_batch--;
      notify_bresults(*m_pres);
      BOOST_LOG_SEV(lg_dcdf_ge, logging::INFO)
        << "process done, remain batch: " << m_remain_batch
        << ", data pool cache: " << m_bdata.size();
    }

    // 算法后处理
    if (m_post_proc && 0 == m_remain_batch) {
      m_post_proc = false;
      std::unique_ptr<algorithm::result> pres = std::move(m_pres);
      // 重置结果数据
      m_pres = std::unique_ptr<algorithm::result>(new algorithm::result);
      m_ge->post_process(pres.get());
      notify_sresults(std::move(pres));
      update_sid = true;
    }
  }
}

}  // namespace algorithm
