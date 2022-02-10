/**
 * @file calibrate.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <chrono>
#include <functional>
#include <memory>
#include <thread>
#include "calibrate/calibrate.h"
#include "logging/log.h"
#include "module/board/board.h"
#include "module/camera/common.h"

namespace calibrate {

boost::log::sources::severity_logger<logging::severity_level> cal_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(cal_lg, "Module", "CALIB");

class cal_board : public board::board_observer {
 public:
  explicit cal_board(std::string uid, std::function<void(std::uint32_t)> status_cb)
      : m_uid(uid), m_status_cb(status_cb) {}
  void handle_frame(std::string uid, board::frame f) override {}
  void handle_status(std::string uid, std::uint32_t s) override {
    if (m_uid == uid && m_status_cb) m_status_cb(s);
  }

 private:
  std::string m_uid;
  std::function<void(std::uint32_t)> m_status_cb;
};

calibrator::calibrator(
    std::shared_ptr<camera::camera> ucam,
    std::shared_ptr<camera::camera> dcam,
    std::shared_ptr<board::board> bd,
    std::string grain_type,
    std::string abnormal_type)
    : m_run(false),
    m_ulight(false),
    m_dlight(false),
    m_inturn(false),
    m_busy(false),
    m_ucam(ucam),
    m_dcam(dcam),
    m_board(bd),
    m_cur_id(0),
    m_grain_type(grain_type),
    m_abnormal_type(abnormal_type) {
  // 启动相机 - 主动获取流方式
  m_ucam->start();
  m_dcam->start();
  m_board_obs = std::make_shared<cal_board>(m_board->uid(),
      std::bind(&calibrator::board_status, this, std::placeholders::_1));
  m_board->attach(m_board_obs);
}

calibrator::~calibrator() {
  m_board->detach(m_board_obs);
  m_ucam->stop();
  m_dcam->stop();
  m_run = false;
  m_ulight = false;
  m_dlight = false;
  m_inturn = false;
  m_observers.clear();
  m_executor.join();
}

int calibrator::stop() {
  int ret = m_board->stop_task();
  if (ret == 0) m_run = false;
  m_cur_id = 0;
  return ret;
}

int calibrator::run(bool switch_on) {
  if (switch_on == m_run) return 0;
  int ret = 0;
  // 开始任务
  if (switch_on) {
    if (board::e_task::im_calibrate != m_board->task()) {
      // 设置控制板任务为校准
      ret = m_board->task(board::e_task::im_calibrate);
      if (0 != ret) return ret;
    }
    ret = m_board->start_task();
    if (0 != ret) return ret;
    m_run = true;
    // m_state = state::dcdf_acquire;
  } else {  // 暂停任务
    int ret = m_board->pasue_task();
    if (0 == ret) {
      m_run = false;
      // m_state = state::none;
    }
  }
  return ret;
}

int calibrator::ulight(bool switch_on) {
  if (m_ulight == switch_on) return 0;
  int ret = 0;
  if (switch_on) {
    // 点亮上光源
    ret = m_board->light_on(ulight_id);
    if (0 != ret) return ret;
    m_ulight = true;
    // m_state = state::ulight_acquire;
    boost::asio::post(m_executor, [this] {
      // 设置上相机反射曝光时间
      m_ucam->exposure_time(m_ca_ret);
      // 设置下相机透射曝光时间
      m_dcam->exposure_time(m_cb_tet);
      // 等待光源点亮1.5秒后开始取图
      std::this_thread::sleep_for(std::chrono::milliseconds(light_on_milliseconds));
      int cam_ret = 0;
      while (m_ulight) {
        // 点亮上光源
        m_board->light_on(ulight_id);
        // 上相机取图
        std::shared_ptr<camera::frame> ua(new camera::frame);
        while (true) {
          cam_ret = m_ucam->get_frame(ua.get());
          if (cam_ret == 0) break;  // 图像采集成功
          BOOST_LOG_SEV(cal_lg, logging::MINOR) << "UA frame lost, ret: " << cam_ret;
        }
        // 下相机取图
        std::shared_ptr<camera::frame> db(new camera::frame);
        while (true) {
          cam_ret = m_dcam->get_frame(db.get());
          if (cam_ret == 0) break;  // 图像采集成功
          BOOST_LOG_SEV(cal_lg, logging::MINOR) << "DB frame lost, ret: " << cam_ret;
        }
        notify_frame(state::ulight_acquire, ua, db, nullptr, nullptr);
      }
      // 关闭上灯
      m_board->light_off(ulight_id);
      BOOST_LOG_SEV(cal_lg, logging::INFO) << "ulight finished";
    });
  } else {
    m_ulight = false;
    // m_state = state::none;
  }
  return ret;
}

int calibrator::dlight(bool switch_on) {
  if (m_dlight == switch_on) return 0;
  int ret = 0;
  if (switch_on) {
    // 点亮下光源
    ret = m_board->light_on(dlight_id);
    if (0 != ret) return ret;
    m_dlight = true;
    // m_state = state::dlight_acquire;
    boost::asio::post(m_executor, [this] {
      // 设置上相机透射曝光时间
      m_ucam->exposure_time(m_ca_tet);
      // 设置下相机反射曝光时间
      m_dcam->exposure_time(m_cb_ret);
      // 等待光源点亮1.5秒后开始取图
      std::this_thread::sleep_for(std::chrono::milliseconds(light_on_milliseconds));
      int cam_ret = 0;
      while (m_dlight) {
        // 点亮下光源
        m_board->light_on(dlight_id);
        // 上相机取图
        std::shared_ptr<camera::frame> da(new camera::frame);
        while (true) {
          cam_ret = m_ucam->get_frame(da.get());
          if (cam_ret == 0) break;
          BOOST_LOG_SEV(cal_lg, logging::MINOR) << "DA frame lost, ret: " << cam_ret;
        }
        // 下相机取图
        std::shared_ptr<camera::frame> ub(new camera::frame);
        while (true) {
          cam_ret = m_dcam->get_frame(ub.get());
          if (cam_ret == 0) break;
          BOOST_LOG_SEV(cal_lg, logging::MINOR) << "UB frame lost, ret: " << cam_ret;
        }
        notify_frame(state::dlight_acquire, nullptr, nullptr, da, ub);
      }
      // 关闭下灯
      m_board->light_off(dlight_id);
      BOOST_LOG_SEV(cal_lg, logging::INFO) << "dlight finished";
    });
  } else {
    m_dlight = false;
    // m_state = state::none;
  }
  return ret;
}

int calibrator::inturn(bool switch_on) {
  if (m_inturn == switch_on) return 0;
  int ret = 0;
  if (switch_on) {
    m_inturn = true;
    // m_state = state::inturn_acquire;
    boost::asio::post(m_executor, [this] {
      while (m_inturn) {
        grab_dcdf(state::inturn_acquire);
      }
      BOOST_LOG_SEV(cal_lg, logging::INFO) << "inturn finished";
    });
  } else {
    m_inturn = false;
    // m_state = state::none;
  }
  return ret;
}

/**
 * @brief 设置相机的反射曝光时间
 * 
 * @param uid 相机uid
 * @param exposure_time 曝光时间
 */
void calibrator::set_reflection_exposure(std::string uid, std::uint32_t exposure_time) {
  if (uid == m_ucam->uid()) {
    m_ca_ret = exposure_time;
    m_ucam->exposure_time(m_ca_ret);
    BOOST_LOG_SEV(cal_lg, logging::DATA) << "set A reflection: " << m_ca_ret;
  }

  if (uid == m_dcam->uid()) {
    m_cb_ret = exposure_time;
    m_dcam->exposure_time(m_cb_ret);
    BOOST_LOG_SEV(cal_lg, logging::DATA) << "set B reflection: " << m_cb_ret;
  }
}

/**
 * @brief 设置相机的透射曝光时间
 * 
 * @param uid 相机uid
 * @param exposure_time 曝光时间
 */
void calibrator::set_transmission_exposure(std::string uid, std::uint32_t exposure_time) {
  if (uid == m_ucam->uid()) {
    m_ca_tet = exposure_time;
    m_ucam->exposure_time(m_ca_tet);
    BOOST_LOG_SEV(cal_lg, logging::DATA) << "set A transmission: " << m_ca_tet;
  }

  if (uid == m_dcam->uid()) {
    m_cb_tet = exposure_time;
    m_dcam->exposure_time(m_cb_tet);
    BOOST_LOG_SEV(cal_lg, logging::DATA) << "set B transmission: " << m_cb_tet;
  }
}

/**
 * @brief Set the grain type object
 * 
 * @param t 谷物类型，使用dev.h中定义的宏
 */
void calibrator::set_grain_type(std::string t) {
  m_grain_type = t;
}

/**
 * @brief Set the abnormal type object
 * 
 * @param t 谷物颗粒类型，使用dev.h中定义的宏
 */
void calibrator::set_abnormal_type(std::string t) {
  m_abnormal_type = t;
}

void calibrator::attach(std::shared_ptr<calibrate_obs> obs) {
  for (const auto &it : m_observers) if (it == obs) return;
  m_observers.push_back(obs);
}

void calibrator::detach(std::shared_ptr<calibrate_obs> obs) {
  m_observers.remove(obs);
}

void calibrator::notify_frame(
    state s,
    std::shared_ptr<camera::frame> ua,
    std::shared_ptr<camera::frame> db,
    std::shared_ptr<camera::frame> da,
    std::shared_ptr<camera::frame> ub) {
  std::time_t tcur = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  char time_str[16];
  std::strftime(time_str, sizeof(time_str), "%Y%m%d%H%M%S", std::localtime(&tcur));
  for (const auto& obs : m_observers) {
    obs->calibrate_frame({
      s, ua, db, da, ub, 0.f, m_cur_id, time_str, m_grain_type, m_abnormal_type});
  }
  m_cur_id++;
}

void calibrator::grab_dcdf(state s) {
  int cam_ret = 0;
  if (s == state::dcdf_acquire) {
    if (m_busy) {
      BOOST_LOG_SEV(cal_lg, logging::MINOR) << "calibrate: dcdf trigger is busy";
      return;
    }
    m_busy = true;
    // 发送上相机开始数据抓取
    m_board->camera_frame_acquire(u_camera_id, start_acquire);
  }
  // 设置上相机反射曝光时间
  m_ucam->exposure_time(m_ca_ret);
  // 设置下相机透射曝光时间
  m_dcam->exposure_time(m_cb_tet);
  BOOST_LOG_SEV(cal_lg, logging::DATA) << "set exposure time: A-reflect(" << m_ca_ret
    << "), B-transmission(" << m_cb_tet << ")";
  // 点亮上光源
  m_board->light_on(ulight_id);
  std::this_thread::sleep_for(std::chrono::milliseconds(light_on_milliseconds));
  // 上相机取图
  std::shared_ptr<camera::frame> ua(new camera::frame);
  while (true) {
    cam_ret = m_ucam->get_frame(ua.get());
    if (cam_ret == 0) break;  // 图像采集成功
    BOOST_LOG_SEV(cal_lg, logging::MINOR) << "UA frame lost, ret: " << cam_ret;
  }
  // 下相机取图
  std::shared_ptr<camera::frame> db(new camera::frame);
  while (true) {
    cam_ret = m_dcam->get_frame(db.get());
    if (cam_ret == 0) break;  // 图像采集成功
    BOOST_LOG_SEV(cal_lg, logging::MINOR) << "DB frame lost, ret: " << cam_ret;
  }
  // 关闭上光源
  m_board->light_off(ulight_id);
  // 设置上相机透射曝光时间
  m_ucam->exposure_time(m_ca_tet);
  // 设置下相机反射曝光时间
  m_dcam->exposure_time(m_cb_ret);
  BOOST_LOG_SEV(cal_lg, logging::DATA) << "set exposure time: A-transmission(" << m_ca_tet
    << "), B-reflection(" << m_cb_ret << ")";
  // 点亮下光源
  m_board->light_on(dlight_id);
  std::this_thread::sleep_for(std::chrono::milliseconds(light_on_milliseconds));
  // 上相机取图
  std::shared_ptr<camera::frame> da(new camera::frame);
  while (true) {
    cam_ret = m_ucam->get_frame(da.get());
    if (cam_ret == 0) break;
    BOOST_LOG_SEV(cal_lg, logging::MINOR) << "DA frame lost, ret: " << cam_ret;
  }
  // 下相机取图
  std::shared_ptr<camera::frame> ub(new camera::frame);
  while (true) {
    cam_ret = m_dcam->get_frame(ub.get());
    if (cam_ret == 0) break;
    BOOST_LOG_SEV(cal_lg, logging::MINOR) << "UB frame lost, ret: " << cam_ret;
  }
  // 关闭下光源
  m_board->light_off(dlight_id);
  // 如果是正常逻辑，则需要通知控制板相机抓图完成
  if (s == state::dcdf_acquire) {
    // 发送下相机数据抓取完成
    m_board->camera_frame_acquire(d_camera_id, finish_acquire);
  }
  notify_frame(s, ua, db, da, ub);
  m_busy = false;
}

void calibrator::board_status(std::uint32_t s) {
  switch (s) {
  case BOARD_STATUS_GRAB_READY:
    if (m_run) boost::asio::post(m_executor, std::bind(&calibrator::grab_dcdf, this, state::dcdf_acquire));
  break;
  default: break;
  }
}

}  // namespace calibrate
