/**
 * @file camera.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "module/camera/camera.h"
#include "module/camera/camera_api.hpp"
#include "logging/log.h"

#include <iostream>
#include <string>
#include <utility>

namespace camera {

boost::log::sources::severity_logger<logging::severity_level> cam_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(cam_lg, "Module", "CAMERA");

camera::camera(std::string uid, boost::shared_ptr<GCamera::CameraApi> driver)
    : camera_subject(uid), m_driver(driver), m_stop(true), m_frame_lost(0) {
  // 打开相机
  GCamera::CameraError ret = driver->openCamera(uid);
  if (GCamera::CameraError::OK != ret) {
    m_ready = false;
    return;
  }
  // 获取相机信息
  GCamera::CameraInfo info;
  ret = driver->infoCamera(uid, &info);
  if (GCamera::CameraError::OK != ret) {
    m_ready = false;
    return;
  }
  m_ready = true;
  // 初始化相机信息
  m_mac = info.mac;
  m_ip = info.ip;

  m_max_h = info.max_h;
  m_max_w = info.max_w;

  m_trigger_delay = info.trigger_delay[0];
  m_min_trigger_delay = info.trigger_delay[1];
  m_max_trigger_delay = info.trigger_delay[2];

  m_exposure_time = info.exposure.time[0];
  m_min_exposure_time = info.exposure.time[1];
  m_max_exposure_time = info.exposure.time[2];

  m_exposure_gain = info.exposure.gain[0];
  m_min_exposure_gain = info.exposure.gain[1];
  m_max_exposure_gain = info.exposure.gain[2];

  m_rgain = info.gains.digital_r[0];
  m_min_rgain = info.gains.digital_r[1];
  m_max_rgain = info.gains.digital_r[2];

  m_ggain = info.gains.digital_g[0];
  m_min_ggain = info.gains.digital_g[1];
  m_max_ggain = info.gains.digital_g[2];

  m_bgain = info.gains.digital_b[0];
  m_min_bgain = info.gains.digital_b[1];
  m_max_bgain = info.gains.digital_b[2];

  m_vflip = info.vflip;
  m_hflip = info.hflip;
  m_trig_mode = t_trig_mode::not_trig;
}

camera::~camera() {
  stop();
  m_driver->closeCamera(m_uid);
}

int camera::start() {
  if (!m_ready) return 1;   // 相机未就绪
  if (!m_stop) return 0;    // 相机已经启动
  GCamera::CameraError ret = m_driver->startCamera(m_uid);
  if (ret != GCamera::CameraError::OK) return 2;
  m_stop = false;
  return 0;
}

int camera::stop() {
  if (!m_ready) return 1;   // 相机未就绪
  if (m_stop) return 0;     // 相机已经停止
  GCamera::CameraError ret = m_driver->stopCamera(m_uid);
  if (ret != GCamera::CameraError::OK) return 2;
  m_stop = true;
  m_frame_lost = 0;
  return 0;
}

int camera::trigger_delay(std::uint32_t delay) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setTriggerDelay(m_uid, delay);
  if (GCamera::CameraError::OK != ret) return 2;
  m_trigger_delay = delay;
  return 0;
}

int camera::exposure_time(std::uint32_t time) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setCameraExposure(m_uid, time);
  if (GCamera::CameraError::OK != ret) return 2;
  m_exposure_gain = time;
  return 0;
}

int camera::exposure_gain(std::uint32_t gain) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setCameraGainExposure(m_uid, gain);
  if (GCamera::CameraError::OK != ret) return 2;
  m_exposure_gain = gain;
  return 0;
}

int camera::rgain(std::uint32_t gain) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setCameraGainR(m_uid, gain);
  if (GCamera::CameraError::OK != ret) return 2;
  m_rgain = gain;
  return 0;
}

int camera::ggain(std::uint32_t gain) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setCameraGainG(m_uid, gain);
  if (GCamera::CameraError::OK != ret) return 2;
  m_ggain = gain;
  return 0;
}

int camera::bgain(std::uint32_t gain) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setCameraGainB(m_uid, gain);
  if (GCamera::CameraError::OK != ret) return 2;
  m_bgain = gain;
  return 0;
}

int camera::vflip(bool flip) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setVerticalFlip(m_uid, flip);
  if (GCamera::CameraError::OK != ret) return 2;
  m_vflip = flip;
  return 0;
}

int camera::hflip(bool flip) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setHorizontalFlip(m_uid, flip);
  if (GCamera::CameraError::OK != ret) return 2;
  m_hflip = flip;
  return 0;
}

int camera::trigger_mode(t_trig_mode mode) {
  if (!m_ready) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->setTriggerMode(m_uid, static_cast<GCamera::TriggerMode>(mode));
  if (GCamera::CameraError::OK != ret) return 2;
  m_trig_mode = mode;
  return 0;
}

int camera::trigger(std::uint32_t timeout_milliseconds, std::uint32_t timeout_id) {
  if (!m_ready || m_stop) return 1;   // 相机未就绪
  if (m_trig_mode != t_trig_mode::software) return 2;   // 触发模式不匹配
  GCamera::CameraError ret = m_driver->softTrigger(m_uid);
  if (GCamera::CameraError::OK != ret) return 2;
  return frame_timeout_detect(timeout_milliseconds, timeout_id);
}

int camera::get_frame(frame* frame) {
  if (!m_ready || m_stop) return 1;   // 相机未就绪
  GCamera::FrameInfo tmp_frame;
  GCamera::CameraError ret = m_driver->getFrame(m_uid, &tmp_frame);
  if (GCamera::CameraError::OK != ret) {
    m_frame_lost++;
    BOOST_LOG_SEV(cam_lg, logging::MAJOR)
      << "get frame failed with: " << static_cast<int>(ret)
      << ", frame lost count: " << m_frame_lost;
    return 2;
  }
  frame->uid = m_uid;
  frame->w = tmp_frame.w;
  frame->h = tmp_frame.h;
  frame->data = tmp_frame.data;
  notify_frame({m_uid, tmp_frame.w, tmp_frame.h, tmp_frame.data});
  return 0;
}

/**
 * @brief Get the frame rate object
 * 
 * @param rate 
 * @return int 
 */
int camera::get_frame_rate(float* rate, std::uint32_t* lost_count) {
  if (!m_ready || m_stop) return 1;   // 相机未就绪
  GCamera::CameraError ret = m_driver->getFrameRate(m_uid, rate);
  if (GCamera::CameraError::OK != ret) {
    BOOST_LOG_SEV(cam_lg, logging::MINOR) << "get frame rate failed: " << static_cast<int>(ret);
    *rate = 0.f;
    return 2;
  }
  *lost_count = m_frame_lost;
  return 0;
}

}  // namespace camera
