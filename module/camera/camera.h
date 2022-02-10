/**
 * @file camera.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODULE_CAMERA_CAMERA_H_
#define MODULE_CAMERA_CAMERA_H_

#include <list>
#include <mutex>
#include <condition_variable>
#include <future>
#include <string>
#include <memory>

#include <boost/asio.hpp>

#include "module/camera/common.h"
#include "module/camera/camera_api.hpp"

// 上相机IP地址
#define UP_CAM_IP "223.254.1.1"
// 下相机IP地址
#define DN_CAM_IP "223.254.2.1"
// 物料监控相机IP地址
#define FC_CAM_IP "223.254.3.1"

/// 上相机序号
constexpr int u_camera_id = 0;
/// 下相机序号
constexpr int d_camera_id = 1;
/// 物料监控相机序号
constexpr int fc_camera_id = 2;
/// 相机开始取图
constexpr int start_acquire = 1;
/// 相机结束取图
constexpr int finish_acquire = 2;

namespace camera {

class camera;
class camera_subject {
 public:
  explicit camera_subject(std::string uid) : m_uid(uid), m_is_busy(false) {}
  virtual ~camera_subject() {
    m_observers.clear();
  }

  void attach(std::shared_ptr<camera_observer> obs) {
    for (const auto &it : m_observers) if (it == obs) return;
    m_observers.push_back(obs);
  }

  void detach(std::shared_ptr<camera_observer> obs) {
    m_observers.remove(obs);
  }

  void notify_frame(frame frame) {
    m_cond_timer.notify_all();
    for (auto& obs : m_observers) {
      obs->handle_frame(frame);
    }
  }

  /**
   * @brief 相机帧超时检测，如果超时则会产生一个超时帧(无效帧)
   * 
   * @param timeout_milliseconds 0不进行超时检测
   */
  int frame_timeout_detect(std::uint32_t timeout_milliseconds, std::uint32_t timeout_id = 0) {
    if (0 == timeout_milliseconds) return 0;
    // if (m_is_busy) return 3;
    // m_is_busy = true;
    auto ret = std::async(std::launch::async, [timeout_milliseconds, timeout_id, this] {
      std::unique_lock<std::mutex> lock_timer(m_mutex_timer);
      std::cv_status timeout_status = m_cond_timer.wait_for(lock_timer,
          std::chrono::milliseconds(timeout_milliseconds));
      if (timeout_status == std::cv_status::timeout) {
        // notify一个无效帧
        notify_frame({m_uid, timeout_id, timeout_id, nullptr});
      }
      // m_is_busy = false;
    });
    return 0;
  }

 protected:
  std::string m_uid;

 private:
  std::list<std::shared_ptr<camera_observer>> m_observers;
  bool m_is_busy;
  std::mutex m_mutex_timer;
  std::condition_variable m_cond_timer;
};

class camera : public camera_subject, public std::enable_shared_from_this<camera> {
 public:
  /**
   * @brief Construct a new camera object
   * 
   * @param uid 相机UUID，由相机插件提供
   * @param driver 相机驱动指针，由相机插件提供
   */
  explicit camera(std::string uid, boost::shared_ptr<GCamera::CameraApi> driver);

  /**
   * @brief Destroy the camera object
   * 
   */
  ~camera();

  /**
   * @brief 相机是否就绪
   * 
   * @return true 相机已就绪
   * @return false 相机未就绪
   */
  bool is_ready() const {return m_ready;}

  /**
   * @brief 
   * 
   * @return int 
   */
  int start();

  /**
   * @brief 
   * 
   * @return int 
   */
  int stop();

  /**
   * @brief 获取相机序号
   * 
   * @return int 相机序号，小于0时，异常
   */
  std::string uid() const {return m_uid;}

  /**
   * @brief 获取相机IP地址
   * 
   * @return std::string 相机IP地址
   */
  std::string ip() const {return m_ip;}

  /**
   * @brief 获取相机MAC地址
   * 
   * @return std::string 相机MAC地址
   */
  std::string mac() const {return m_mac;}

  /**
   * @brief 获取相机图像最大宽度
   * 
   * @return std::uint32_t 相机最大宽度
   */
  std::uint32_t max_w() const {return m_max_w;}

  /**
   * @brief 获取相机图像最大高度
   * 
   * @return std::uint32_t 相机最大高度
   */
  std::uint32_t max_h() const {return m_max_h;}

  /**
   * @brief 获取相机触发延迟时间
   * 
   * @return std::uint32_t 触发延迟时间
   */
  std::uint32_t trigger_delay() const {return m_trigger_delay;}

  /**
   * @brief 获取相机曝光时间
   * 
   * @return std::uint32_t 相机曝光时间
   */
  std::uint32_t exposure_time() const {return m_exposure_time;}

  /**
   * @brief 获取相机曝光增益
   * 
   * @return std::uint32_t 相机曝光增益
   */
  std::uint32_t exposure_gain() const {return m_exposure_gain;}

  /**
   * @brief 获取相机R通道数字增益
   * 
   * @return std::uint32_t 相机R通道数字增益
   */
  std::uint32_t rgain() const {return m_rgain;}

  /**
   * @brief 获取相机G通道数字增益
   * 
   * @return std::uint32_t 相机G通道数字增益
   */
  std::uint32_t ggain() const {return m_ggain;}

  /**
   * @brief 获取相机B通道数字增益
   * 
   * @return std::uint32_t 相机B通道数字增益
   */
  std::uint32_t bgain() const {return m_bgain;}

  /**
   * @brief 检查相机是否设置了图像垂直翻转
   * 
   * @return true 相机设置了垂直翻转
   * @return false 相机未设置垂直翻转
   */
  bool vflip() const {return m_vflip;}

  /**
   * @brief 检查相机是否设置了图像水平翻转
   * 
   * @return true 相机设置了水平翻转
   * @return false 相机未设置水平翻转
   */
  bool hflip() const {return m_hflip;}

  /**
   * @brief 检查相机是否设置了软件触发
   * 
   * @return true 相机设置了软件触发
   * @return false 相机设置了硬件触发
   */
  t_trig_mode trigger_mode() const {return m_trig_mode;}

  /**
   * @brief 设置相机触发延迟时间
   * 
   * @param delay 相机触发延迟时间
   * @return int 错误码
   */
  int trigger_delay(std::uint32_t delay);

  /**
   * @brief 设置相机曝光时间
   * 
   * @param time 相机曝光时间
   * @return int 错误码
   */
  int exposure_time(std::uint32_t time);

  /**
   * @brief 设置相机曝光增益
   * 
   * @param gain 相机曝光增益
   * @return int 错误码
   */
  int exposure_gain(std::uint32_t gain);

  /**
   * @brief 设置相机R通道数字增益
   * 
   * @param gain R通道数字增益
   * @return int 错误码
   */
  int rgain(std::uint32_t gain);

  /**
   * @brief 设置相机G通道数字增益
   * 
   * @param gain G通道数字增益
   * @return int 错误码
   */
  int ggain(std::uint32_t gain);

  /**
   * @brief 设置相机B通道数字增益
   * 
   * @param gain B通道数字增益
   * @return int 错误码
   */
  int bgain(std::uint32_t gain);

  /**
   * @brief 设置相机图像垂直翻转属性
   * 
   * @param flip 是否进行图像垂直翻转
   * @return int 错误码
   */
  int vflip(bool flip);

  /**
   * @brief 设置相机图像水平翻转属性
   * 
   * @param flip 是否进行图像水平翻转
   * @return int 错误码
   */
  int hflip(bool flip);

  /**
   * @brief 设置相机触发模式
   * 
   * @param t_trig_mode 触发模式
   * @return int 错误码
   */
  int trigger_mode(t_trig_mode mode);

  /**
   * @brief 给相机一个软件触发信号
   * 
   * @param with_tiemout 帧超时，为0时不进行超时检测
   * @return int 
   */
  int trigger(std::uint32_t timeout_milliseconds = 0, std::uint32_t timeout_id = 0);

  /**
   * @brief Get the frame object
   * 
   * @param frame 
   * @return int 
   */
  int get_frame(frame* frame);

  /**
   * @brief Get the frame rate object
   * 
   * @param rate 采集帧率
   * @param lost_count 丢图数量
   * @return int 
   */
  int get_frame_rate(float* rate, std::uint32_t* lost_count);

  /**
   * @brief 触发延时范围
   * 
   * @param min 最小值
   * @param max 最大值
   */
  void trigger_delay_range(std::uint32_t* min, std::uint32_t* max) {
    *min = m_min_trigger_delay;
    *max = m_max_trigger_delay;
  }

  /**
   * @brief 曝光时间范围
   * 
   * @param min 最小值
   * @param max 最大值
   */
  void exposure_time_range(std::uint32_t* min, std::uint32_t* max) {
    *min = m_min_exposure_time;
    *max = m_max_exposure_time;
  }

  /**
   * @brief 曝光增益范围
   * 
   * @param min 最小值
   * @param max 最大值
   */
  void exposure_gain_range(std::uint32_t* min, std::uint32_t* max) {
    *min = m_min_exposure_gain;
    *max = m_max_exposure_gain;
  }

  /**
   * @brief R通道增益范围
   * 
   * @param min 最小值
   * @param max 最大值
   */
  void rgain_range(std::uint32_t* min, std::uint32_t* max) {
    *min = m_min_rgain;
    *max = m_max_rgain;
  }

  /**
   * @brief G通道增益范围
   * 
   * @param min 最小值
   * @param max 最大值
   */
  void ggain_range(std::uint32_t* min, std::uint32_t* max) {
    *min = m_min_ggain;
    *max = m_max_ggain;
  }

  /**
   * @brief B通道增益范围
   * 
   * @param min 最小值
   * @param max 最大值
   */
  void bgain_range(std::uint32_t* min, std::uint32_t* max) {
    *min = m_min_bgain;
    *max = m_max_bgain;
  }

 private:
  std::string m_mac;
  std::string m_ip;

  std::uint32_t m_max_w;
  std::uint32_t m_max_h;

  std::uint32_t m_trigger_delay;
  std::uint32_t m_max_trigger_delay;
  std::uint32_t m_min_trigger_delay;

  std::uint32_t m_exposure_time;
  std::uint32_t m_max_exposure_time;
  std::uint32_t m_min_exposure_time;

  std::uint32_t m_exposure_gain;
  std::uint32_t m_max_exposure_gain;
  std::uint32_t m_min_exposure_gain;

  std::uint32_t m_rgain;
  std::uint32_t m_max_rgain;
  std::uint32_t m_min_rgain;

  std::uint32_t m_ggain;
  std::uint32_t m_max_ggain;
  std::uint32_t m_min_ggain;

  std::uint32_t m_bgain;
  std::uint32_t m_max_bgain;
  std::uint32_t m_min_bgain;

  t_trig_mode m_trig_mode;

  // 相机丢帧数
  std::uint32_t m_frame_lost;

  bool m_vflip;
  bool m_hflip;
  // bool m_software_trigger;
  bool m_ready;
  bool m_stop;

  boost::shared_ptr<GCamera::CameraApi> m_driver;
};

}  // namespace camera

#endif  // MODULE_CAMERA_CAMERA_H_
