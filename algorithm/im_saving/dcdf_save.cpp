/**
 * @file dcdf_save.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <functional>
#include <sstream>
#include <regex>
#include <boost/filesystem.hpp>
#include <boost/filesystem/file_status.hpp>
#include <boost/asio/thread_pool.hpp>
#include <opencv2/opencv.hpp>

#include "logging/log.h"
#include "algorithm/im_saving/dcdf_save.h"
#include "generator/dcdf_generator.h"
#include "calibrate/calibrate.h"

namespace algorithm {

boost::log::sources::severity_logger<logging::severity_level> imsave_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(imsave_lg, "Module", "IM_SAVE");

class dcdf_obs : public generator::dcdf_obs_frame {
 public:
  explicit dcdf_obs(std::function<void(batch_frame frame, tengine engine)> frame_cb) : m_cb(frame_cb) {}
  void handle_frame(generator::dcdf_frame f) override {
    if (m_cb) {
      m_cb({f.ua, f.db, f.da, f.ub, f.wei, f.id, f.time_str, f.grain_type, f.abnormal_type}, tengine::dcdf);
    }
  }

 private:
  std::function<void(batch_frame frame, tengine engine)> m_cb;
};

class cali_obs : public calibrate::calibrate_obs {
 public:
  explicit cali_obs(std::function<void(batch_frame frame, tengine engine)> frame_cb) : m_cb(frame_cb) {}
  void calibrate_frame(calibrate::frame f) override {
    if (m_cb) {
      m_cb({f.ua, f.db, f.da, f.ub, f.wei, f.id, f.time_str, f.grain_type, f.abnormal_type}, tengine::calibrator);
    }
  }

 private:
  std::function<void(batch_frame frame, tengine engine)> m_cb;
};

dcdf_save::dcdf_save(std::shared_ptr<generator::dcdf_engine> dcdf_engine,
    std::shared_ptr<calibrate::calibrator> cali_engine,
    std::string sv_path, std::string device_id)
    : m_save_enable(false),
      m_dcdf_engine(dcdf_engine),
      m_cali_engine(cali_engine),
      m_path(sv_path),
      m_dev_id(device_id),
      m_remain(0) {
  m_dcdf_obs = std::make_shared<dcdf_obs>(
    std::bind(&dcdf_save::save_entity, this, std::placeholders::_1, std::placeholders::_2));
  if (m_dcdf_engine) m_dcdf_engine->attach(m_dcdf_obs);
  m_cali_obs = std::make_shared<cali_obs>(
    std::bind(&dcdf_save::save_entity, this, std::placeholders::_1, std::placeholders::_2));
  if (m_cali_engine) m_cali_engine->attach(m_cali_obs);
}

dcdf_save::~dcdf_save() {
  if (m_dcdf_engine) m_dcdf_engine->detach(m_dcdf_obs);
  if (m_cali_engine) m_cali_engine->detach(m_cali_obs);
  m_save_enable = false;
  m_remain = 0;
  m_tpool.join();
}

int dcdf_save::set_path(std::string path) {
  m_path = path;
  try {
    if (!boost::filesystem::exists(m_path) || !boost::filesystem::is_directory(m_path)) {
      boost::filesystem::create_directory(m_path);
    }
  } catch(...) {
    m_save_enable = false;
    // create directory to save image failed
    return 1;
  }
  return 0;
}

int dcdf_save::enable() {
  m_save_enable = true;
  return set_path(m_path);  // valid saving path checking
}

int dcdf_save::disable() {
  m_save_enable = false;
  return 0;
}


std::regex im_type("_GZ_");

void dcdf_save::save_entity(batch_frame f, tengine engine) {
  if (!m_save_enable) return;
  float wei = f.wei;
  // common name
  std::stringstream ss_common_name;
  ss_common_name << m_path << m_dev_id << "_6_" << f.time_str << "_" << f.id << "_" << f.grain_type
    << "_" << f.abnormal_type << "_GZ_" << std::fixed << std::setprecision(3) << f.wei << ".png";
  std::string common_name = ss_common_name.str();

  if (f.ua) {
    m_remain++;
    std::string ua_name = std::regex_replace(common_name, im_type, "_UA_");
    std::shared_ptr<camera::frame> fua = f.ua;
    boost::asio::post(m_tpool, [this, ua_name, fua] {
      cv::imwrite(ua_name.c_str(), cv::Mat(fua->h, fua->w, CV_8UC3, fua->data.get()));
      m_remain--;
    });
  }

  if (f.db) {
    m_remain++;
    std::string db_name = std::regex_replace(common_name, im_type, "_DB_");
    std::shared_ptr<camera::frame> fdb = f.db;
    boost::asio::post(m_tpool, [this, db_name, fdb] {
      cv::imwrite(db_name.c_str(), cv::Mat(fdb->h, fdb->w, CV_8UC3, fdb->data.get()));
      m_remain--;
    });
  }

  if (f.da) {
    m_remain++;
    std::string da_name = std::regex_replace(common_name, im_type, "_DA_");
    std::shared_ptr<camera::frame> fda = f.da;
    boost::asio::post(m_tpool, [this, da_name, fda] {
      cv::imwrite(da_name.c_str(), cv::Mat(fda->h, fda->w, CV_8UC3, fda->data.get()));
      m_remain--;
    });
  }

  if (f.ub) {
    m_remain++;
    std::string ub_name = std::regex_replace(common_name, im_type, "_UB_");
    std::shared_ptr<camera::frame> fub = f.ub;
    boost::asio::post(m_tpool, [this, ub_name, fub] {
      cv::imwrite(ub_name.c_str(), cv::Mat(fub->h, fub->w, CV_8UC3, fub->data.get()));
      m_remain--;
    });
  }
  BOOST_LOG_SEV(imsave_lg, logging::INFO) << "save engine[" << static_cast<int>(engine)
    << "], remain image to save: " << m_remain;
}

}  // namespace algorithm
