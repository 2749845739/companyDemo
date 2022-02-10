/**
 * @file dcdf_generator.h
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-16
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GENERATOR_DCDF_GENERATOR_H_
#define GENERATOR_DCDF_GENERATOR_H_

#include <list>
#include <memory>
#include <map>
#include <string>
#include <queue>

#include "module/camera/common.h"
#include "module/camera/camera.h"
#include "module/board/board.h"

namespace generator {

struct dcdf_frame {
  std::shared_ptr<camera::frame> ua;
  std::shared_ptr<camera::frame> db;
  std::shared_ptr<camera::frame> da;
  std::shared_ptr<camera::frame> ub;
  float wei;
  std::string sid;
  std::uint32_t id;
  std::string time_str;
  std::string grain_type;
  std::string abnormal_type;
};

class dcdf_obs_frame {
 public:
  virtual void handle_frame(dcdf_frame frame) = 0;
};

enum class dcdf_status : std::uint32_t {
  engine_on = 0,                      // dcdf enabled
  engine_off = 1,                     // dcdf disabled
  batch_done,
  sample_done = BOARD_STATUS_READY,   // 样本完成数据采集
};

class dcdf_obs_status {
 public:
  virtual void handle_status(dcdf_status s) = 0;
};

class dcdf_board;

class dcdf_engine {
 public:
  /**
   * @brief 构造一个双相机，双面数据生成器
   * 
   * @param camera_a A相机
   * @param camera_b B相机
   */
  explicit dcdf_engine(
    std::shared_ptr<board::board> pboard,
    std::shared_ptr<camera::camera> camera_a,
    std::shared_ptr<camera::camera> camera_b,
    std::string grain_type,
    std::string abnormal_type);

  /**
   * @brief Destroy the dcdf engine object
   * 
   */
  ~dcdf_engine();

  /**
   * @brief 开始dcdf模块
   * 
   * @return int 
   */
  int start();

  /**
   * @brief 停止dcdf模块
   * 
   * @return int 
   */
  int stop();

  /**
   * @brief 设置相机的反射曝光时间
   * 
   * @param uid 相机uid
   * @param exposure_time 曝光时间
   */
  void set_reflection_exposure(std::string uid, std::uint32_t exposure_time);

  /**
   * @brief 设置相机的透射曝光时间
   * 
   * @param uid 相机uid
   * @param exposure_time 曝光时间
   */
  void set_transmission_exposure(std::string uid, std::uint32_t exposure_time);

  /**
   * @brief Set the grain type object
   * 
   * @param t 谷物类型，使用dev.h中定义的宏
   */
  void set_grain_type(std::string t);

  /**
   * @brief 获取谷物类型
   * 
   * @return std::string dev.h中定义的宏
   */
  std::string grain_type() {return m_grain_type;}

  /**
   * @brief Set the abnormal type object
   * 
   * @param t 谷物颗粒类型，使用dev.h中定义的宏
   */
  void set_abnormal_type(std::string t);

  /**
   * @brief 获取谷物颗粒类型
   * 
   * @return std::string 谷物颗粒类型，dev.h中定义的宏
   */
  std::string abnormal_type() {return m_abnormal_type;}

  /**
   * @brief 生产一组数据，双相机双面数据
   * 
   * @return int 
   */
  int trigger();

  /**
   * @brief 增加数据观察者
   * 
   * @param obs 
   */
  void attach(std::shared_ptr<dcdf_obs_frame> obs);

  /**
   * @brief 删除数据观察者
   * 
   * @param obs 
   */
  void detach(std::shared_ptr<dcdf_obs_frame> obs);

  /**
   * @brief 增加状态观察者
   * 
   * @param obs 
   */
  void attach(std::shared_ptr<dcdf_obs_status> obs);

  /**
   * @brief 删除状态观察者
   * 
   * @param obs 
   */
  void detach(std::shared_ptr<dcdf_obs_status> obs);

 private:
  /**
   * @brief 
   * 
   * @param frame 实现相机数据通知处理函数
   */
  // void handle_frame(camera::frame frame) override;

  /**
   * @brief 处理控制板frame
   * 
   * @param uid 控制板序号
   * @param frame 控制板frame数据
   */
  void handle_board_frame(board::frame frame);

  /**
   * @brief 处理控制板状态
   * 
   * @param uid 控制板序号
   * @param status 
   */
  void handle_board_status(std::uint32_t status);

  /**
   * @brief 数据触发的线程实体函数
   * 
   */
  void trigger_entity();

  /**
   * @brief dcdf engine状态通知
   * 
   */
  void notify_status(dcdf_status s);

  /**
   * @brief 获取当前时间字符串
   * 
   * @return std::string 
   */
  std::string current_time();

 private:
  std::shared_ptr<board::board> m_board;
  std::string m_board_uid;
  bool m_busy;
  bool m_run;
  std::shared_ptr<camera::camera> m_camera_a;
  std::string m_ca_uid;
  std::shared_ptr<camera::camera> m_camera_b;
  std::string m_cb_uid;

  std::queue<dcdf_frame> m_data_pool;

  std::uint32_t m_ca_ret = 223;
  std::uint32_t m_ca_tet = 350;
  std::uint32_t m_cb_ret = 322;
  std::uint32_t m_cb_tet = 400;

  std::thread m_trigger_thread;
  bool m_run_trigger;
  std::condition_variable m_cond_trigger;
  std::mutex m_mutex_trigger;

  bool m_up_light_on;

  /// batch id
  std::uint32_t m_im_count;
  std::uint32_t m_wei_count;
  float m_sample_wei;

  /// sample id
  std::string m_sid;
  bool m_update_sid;

  /// 所有数据观察者
  std::list<std::shared_ptr<dcdf_obs_frame>> m_frame_obs;
  std::list<std::shared_ptr<dcdf_obs_status>> m_status_obs;
  std::shared_ptr<dcdf_board> m_dcdf_board;

  std::string m_grain_type;
  std::string m_abnormal_type;
};

}  // namespace generator

#endif  // GENERATOR_DCDF_GENERATOR_H_
