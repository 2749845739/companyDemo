/**
 * @file dcdf_generator.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <ctime>
#include <iostream>
#include <chrono>
#include <functional>
#include <memory>
#include <thread>

#include <opencv2/opencv.hpp>

#include "generator/dcdf_generator.h"
#include "module/def.h"
#include "module/board/board.h"
#include "logging/log.h"

namespace generator {

boost::log::sources::severity_logger<logging::severity_level> dcdf_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(dcdf_lg, "Module", "DCDF");

class dcdf_board : public board::board_observer {
 public:
  explicit dcdf_board(std::string uid,
      std::function<void(board::frame)> frame_cb,
      std::function<void(std::uint32_t)> status_cb)
      : m_uid(uid), m_frame_cb(frame_cb), m_status_cb(status_cb) {}

  /**
 * @brief 处理控制板frame
 * 
 * @param uid 控制板序号
 * @param frame 控制板frame数据
 */
  void handle_frame(std::string uid, board::frame frame) {
    if (m_uid == uid) {
      m_frame_cb(frame);
    }
  }

  /**
   * @brief 处理控制板状态
   * 
   * @param uid 控制板序号
   * @param status 状态值
   */
  void handle_status(std::string uid, std::uint32_t status) {
    if (m_uid == uid) {
      m_status_cb(status);
    }
  }

 private:
  std::string m_uid;
  std::function<void(board::frame)> m_frame_cb;
  std::function<void(std::uint32_t)> m_status_cb;
};

dcdf_engine::dcdf_engine(
    std::shared_ptr<board::board> pboard,
    std::shared_ptr<camera::camera> camera_a,
    std::shared_ptr<camera::camera> camera_b,
    std::string grain_type,
    std::string abnormal_type)
    : m_board(pboard),
    m_board_uid(pboard->uid()),
    m_camera_a(camera_a),
    m_camera_b(camera_b),
    m_ca_uid(camera_a->uid()),
    m_cb_uid(camera_b->uid()),
    m_run_trigger(true),
    m_busy(false),
    m_run(false),
    m_wei_count(0),
    m_im_count(0),
    m_sample_wei(0.f),
    m_sid(),
    m_update_sid(true),
    m_grain_type(grain_type),
    m_abnormal_type(abnormal_type) {
  m_board->task(board::e_task::unsound);
  m_dcdf_board = std::make_shared<dcdf_board>(m_board->uid(),
    std::bind(&dcdf_engine::handle_board_frame, this, std::placeholders::_1),
    std::bind(&dcdf_engine::handle_board_status, this, std::placeholders::_1));
  // m_board->attach(m_dcdf_board);

  m_camera_a->start();
  m_camera_b->start();

  m_trigger_thread = std::thread([this]{
    while (true) {
      std::unique_lock<std::mutex> lk_trigger(m_mutex_trigger);
      m_cond_trigger.wait(lk_trigger);
      if (!m_run_trigger) break;
      trigger_entity();
    }
  });
}

dcdf_engine::~dcdf_engine() {
  // m_board->detach(m_dcdf_board);
  stop();
  m_frame_obs.clear();
  m_status_obs.clear();
  // 停止trigger线程
  m_run_trigger = false;
  m_cond_trigger.notify_all();
  m_camera_a->stop();
  m_camera_b->stop();
  if (m_trigger_thread.joinable()) m_trigger_thread.join();
  // if (m_im_count != m_wei_count) {
  //   /// todo(djj): error
  // }
}

int dcdf_engine::start() {
  if (m_run) return 0;
  m_board->attach(m_dcdf_board);
  m_run = true;
  notify_status(dcdf_status::engine_on);
  return 0;
}

int dcdf_engine::stop() {
  if (!m_run) return 0;
  m_board->detach(m_dcdf_board);
  m_run = false;
  notify_status(dcdf_status::engine_off);
  return 0;
}

void dcdf_engine::set_reflection_exposure(std::string uid, std::uint32_t exposure_time) {
  if (uid == m_ca_uid) {
    m_ca_ret = exposure_time;
    m_camera_a->exposure_time(m_ca_ret);
    BOOST_LOG_SEV(dcdf_lg, logging::DATA) << "set A reflection: " << m_ca_ret;
  }

  if (uid == m_cb_uid) {
    m_cb_ret = exposure_time;
    m_camera_b->exposure_time(m_cb_ret);
    BOOST_LOG_SEV(dcdf_lg, logging::DATA) << "set B reflection: " << m_cb_ret;
  }
}

void dcdf_engine::set_transmission_exposure(std::string uid, std::uint32_t exposure_time) {
  if (uid == m_ca_uid) {
    m_ca_tet = exposure_time;
    m_camera_a->exposure_time(m_ca_tet);
    BOOST_LOG_SEV(dcdf_lg, logging::DATA) << "set A transmission: " << m_ca_tet;
  }

  if (uid == m_cb_uid) {
    m_cb_tet = exposure_time;
    m_camera_b->exposure_time(m_cb_tet);
    BOOST_LOG_SEV(dcdf_lg, logging::DATA) << "set B transmission: " << m_cb_tet;
  }
}

/**
 * @brief Set the grain type object
 * 
 * @param t 谷物类型，使用dev.h中定义的宏
 */
void dcdf_engine::set_grain_type(std::string t) {
  m_grain_type = t;
}


/**
 * @brief Set the abnormal type object
 * 
 * @param t 谷物颗粒类型，使用dev.h中定义的宏
 */
void dcdf_engine::set_abnormal_type(std::string t) {
  m_abnormal_type = t;
}

int dcdf_engine::trigger() {
  if (m_busy) {
    BOOST_LOG_SEV(dcdf_lg, logging::MAJOR)
      << "trigger is busy, im count: " << m_im_count
      << ", wei count: " << m_wei_count;
    return -1;
  }
  m_busy = true;
  m_cond_trigger.notify_one();
  return 0;
}

void dcdf_engine::attach(std::shared_ptr<dcdf_obs_frame> obs) {
  for (const auto &it : m_frame_obs) if (it == obs) return;
  m_frame_obs.push_back(obs);
}

void dcdf_engine::detach(std::shared_ptr<dcdf_obs_frame> obs) {
  m_frame_obs.remove(obs);
}

/**
 * @brief 增加状态观察者
 * 
 * @param obs 
 */
void dcdf_engine::attach(std::shared_ptr<dcdf_obs_status> obs) {
  for (const auto &it : m_status_obs) if (it == obs) return;
  m_status_obs.push_back(obs);
}

/**
 * @brief 删除状态观察者
 * 
 * @param obs 
 */
void dcdf_engine::detach(std::shared_ptr<dcdf_obs_status> obs) {
  m_status_obs.remove(obs);
}

/**
 * @brief 处理控制板frame
 * 
 * @param uid 控制板序号
 * @param frame 控制板frame数据
 */
void dcdf_engine::handle_board_frame(board::frame frame) {
  if (m_data_pool.empty()) {
    BOOST_LOG_SEV(dcdf_lg, logging::MAJOR)
      << "data pool is empty, but receive weight";
    return;
  }
  dcdf_frame data = m_data_pool.front();
  data.wei = frame.wei;
  m_data_pool.pop();
  m_wei_count++;
  m_sample_wei += data.wei;
  BOOST_LOG_SEV(dcdf_lg, logging::INFO) << "im count: " << m_im_count
      << ", wei count: " << m_wei_count << ", batch weight: " << data.wei
      << ", ---> data cache size: " << m_data_pool.size();
  for (auto& frame_obs : m_frame_obs) {
    frame_obs->handle_frame(data);
  }
  notify_status(dcdf_status::batch_done);
}

void dcdf_engine::handle_board_status(std::uint32_t status) {
  switch (status) {
    // 收到控制板样本抓取就绪指令
    case BOARD_STATUS_GRAB_READY:
      if (m_update_sid) {
        m_update_sid = false;
        m_sid = current_time();
      }
      trigger();  // 触发相机抓取图像
    break;
    // 收到控制停止信号
    case BOARD_STATUS_READY:
      BOOST_LOG_SEV(dcdf_lg, logging::DATA)
        << "\t ++++++++++ total im count: " << m_im_count
        << ", total wei count: " << m_wei_count
        << ", total weights: " << m_sample_wei << "mg";
      if (m_im_count != m_wei_count) {
        /// TODO(djj): 图像数量与质量不匹配异常
        BOOST_LOG_SEV(dcdf_lg, logging::MAJOR)
          << "receive board stop, but im count not match with weight count";
      }
      m_im_count = 0;
      m_wei_count = 0;
      m_sample_wei = 0.f;
      m_update_sid = true;
      notify_status(dcdf_status::sample_done);
    break;
    // 收到控制板运行指令
    case BOARD_STATUS_RUNNING:break;
    // 收到控制板暂停指令
    case BOARD_STATUS_PAUSE:break;
    // 收到控制板异常-无效指令
    case BOARD_STATUS_INVALID:break;
    default:
    break;
  }
}

void dcdf_engine::trigger_entity() {
  // 发送上相机开始数据抓取
  m_board->camera_frame_acquire(u_camera_id, start_acquire);
  // 上光源点亮
  m_board->light_on(ulight_id);

  // std::unique_lock<std::mutex> lk_timeout(m_mutex_frame_timeout);
  m_up_light_on = true;
  m_camera_a->exposure_time(m_ca_ret);  // 设置A相机反射曝光时间
  m_camera_b->exposure_time(m_cb_tet);  // 设置B相机透射曝光时间
  BOOST_LOG_SEV(dcdf_lg, logging::DATA) << "set exposure time: A-reflect(" << m_ca_ret
    << "), B-transmission(" << m_cb_tet << ")";
  // 提前亮灯
  std::this_thread::sleep_for(std::chrono::milliseconds(light_on_milliseconds));
  // A相机取帧
  std::shared_ptr<camera::frame> m_ua = std::make_shared<camera::frame>(camera::frame());
#ifndef TEST_READ_IM
  int cam_ret;
  do {
    cam_ret = m_camera_a->get_frame(m_ua.get());
    if (cam_ret != 0) BOOST_LOG_SEV(dcdf_lg, logging::MAJOR) << "UA frame lost, ret: " << cam_ret;
    // std::cout << "get frame ua ret: " << cam_ret << std::endl;
  } while (cam_ret != 0);
#else
  cv::Mat ua_im = cv::imread("ua.png");
  m_ua->uid = "223.254.1.1";
  m_ua->w = ua_im.cols;
  m_ua->h = ua_im.rows;
  m_ua->data = std::shared_ptr<std::uint8_t>(new std::uint8_t[m_ua->w * m_ua->h * 3]);
  memcpy(m_ua->data.get(), ua_im.data, m_ua->w * m_ua->h * 3);
#endif  // TEST_READ_IM
  // m_camera_b->exposure_time(m_cb_tet);  // 设置B相机透射曝光时间
  // B相机取帧
  std::shared_ptr<camera::frame> m_db = std::make_shared<camera::frame>(camera::frame());
#ifndef TEST_READ_IM
  do {
    cam_ret = m_camera_b->get_frame(m_db.get());
    if (cam_ret != 0) BOOST_LOG_SEV(dcdf_lg, logging::MAJOR) << "DB frame lost, ret: " << cam_ret;
  } while (cam_ret != 0);
#else
  cv::Mat db_im = cv::imread("db.png");
  m_db->uid = "223.254.2.1";
  m_db->w = db_im.cols;
  m_db->h = db_im.rows;
  m_db->data = std::shared_ptr<std::uint8_t>(new std::uint8_t[m_db->w * m_db->h * 3]);
  memcpy(m_db->data.get(), db_im.data, m_db->w * m_db->h * 3);
#endif  // TEST_READ_IM
  // 关闭上光源
  m_board->light_off(ulight_id);
  // 开启下光源
  m_board->light_on(dlight_id);

  // 更改相机曝光时间
  m_camera_a->exposure_time(m_ca_tet);  // 设置A相机透射曝光时间
  m_camera_b->exposure_time(m_cb_ret);  // 设置B相机反射曝光时间
  BOOST_LOG_SEV(dcdf_lg, logging::DATA) << "set exposure time: A-transmission(" << m_ca_tet
    << "), B-reflection(" << m_cb_ret << ")";

  // 提前亮灯
  std::this_thread::sleep_for(std::chrono::milliseconds(light_on_milliseconds));

  m_up_light_on = false;
  // A相机取帧
  std::shared_ptr<camera::frame> m_da = std::make_shared<camera::frame>(camera::frame());
#ifndef TEST_READ_IM
  do {
    cam_ret = m_camera_a->get_frame(m_da.get());
    if (cam_ret != 0) BOOST_LOG_SEV(dcdf_lg, logging::MAJOR) << "DA frame lost, ret: " << cam_ret;
  } while (cam_ret != 0);
#else
  cv::Mat da_im = cv::imread("da.png");
  m_da->uid = "223.254.1.1";
  m_da->w = da_im.cols;
  m_da->h = da_im.rows;
  m_da->data = std::shared_ptr<std::uint8_t>(new std::uint8_t[m_da->w * m_da->h * 3]);
  memcpy(m_da->data.get(), da_im.data, m_da->w * m_da->h * 3);
#endif  // TEST_READ_IM
  // B相机取帧
  std::shared_ptr<camera::frame> m_ub = std::make_shared<camera::frame>(camera::frame());
#ifndef TEST_READ_IM
  do {
    cam_ret = m_camera_b->get_frame(m_ub.get());
    if (cam_ret != 0) BOOST_LOG_SEV(dcdf_lg, logging::MAJOR) << "UB frame lost, ret: " << cam_ret;
  } while (cam_ret != 0);
#else
  cv::Mat ub_im = cv::imread("ub.png");
  m_ub->uid = "223.254.2.1";
  m_ub->w = ub_im.cols;
  m_ub->h = ub_im.rows;
  m_ub->data = std::shared_ptr<std::uint8_t>(new std::uint8_t[m_ub->w * m_ub->h * 3]);
  memcpy(m_ub->data.get(), ub_im.data, m_ub->w * m_ub->h * 3);
#endif  // TEST_READ_IM
  // 关闭下光源
  m_board->light_off(dlight_id);
  // 发送下相机数据抓取完成
  m_board->camera_frame_acquire(d_camera_id, finish_acquire);
  // 完成所有数据帧获取
  std::string time_str = current_time();
  m_data_pool.push({m_ua, m_db, m_da, m_ub, 0.f, m_sid,
    m_im_count, time_str, m_grain_type, m_abnormal_type});
  m_im_count++;
  m_busy = false;
  BOOST_LOG_SEV(dcdf_lg, logging::DATA)
    << "!!!!!!!!!! got dcdf frame, im count: " << m_im_count << "!!!!!!!!!!";
}

void dcdf_engine::notify_status(dcdf_status s) {
  for (auto& status_obs : m_status_obs) {
    status_obs->handle_status(s);
  }
}

std::string dcdf_engine::current_time() {
  std::time_t tcur = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  char time_str[16];
  std::strftime(time_str, sizeof(time_str), "%Y%m%d%H%M%S", std::localtime(&tcur));
  return std::string(time_str);
}

}  // namespace generator
