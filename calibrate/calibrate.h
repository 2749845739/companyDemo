/**
 * @file calibrate.h
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CALIBRATE_CALIBRATE_H_
#define CALIBRATE_CALIBRATE_H_


#include <memory>
#include <list>
#include <string>
#include <boost/asio/thread_pool.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/asio.hpp>

#include "module/camera/camera.h"
#include "module/board/board.h"

namespace calibrate {

class cal_board;

enum class state : std::uint8_t {
  none,
  dcdf_acquire,      // 双面双相机数据抓取完成
  inturn_acquire,    // 循环点相机数据抓取完成
  ulight_acquire,    // 上灯亮相机数据抓取完成
  dlight_acquire,    // 下灯亮相机数据抓取完成
};

struct frame {
  state s;
  std::shared_ptr<camera::frame> ua;
  std::shared_ptr<camera::frame> db;
  std::shared_ptr<camera::frame> da;
  std::shared_ptr<camera::frame> ub;
  float wei;
  std::uint32_t id;
  std::string time_str;
  std::string grain_type;
  std::string abnormal_type;
};

class calibrate_obs {
 public:
  virtual void calibrate_frame(frame f) = 0;
};

class calibrator : private boost::noncopyable {
 public:
  explicit calibrator(
    std::shared_ptr<camera::camera> ucam,
    std::shared_ptr<camera::camera> dcam,
    std::shared_ptr<board::board> bd,
    std::string grain_type,
    std::string abnormal_type);

  ~calibrator();

  /**
   * @brief 停止
   * 
   * @return int 
   */
  int stop();

  /**
   * @brief 开始/暂停
   * 
   * @param switch_on 开始/暂停
   * @return int 
   */
  int run(bool switch_on);

  /**
   * @brief 上光源
   * 
   * @param switch_on 开/关
   * @return int 
   */
  int ulight(bool switch_on);

  /**
   * @brief 下光源
   * 
   * @param switch_on 开/关
   * @return int 
   */
  int dlight(bool switch_on);

  /**
   * @brief 上下光源循环点亮
   * 
   * @param switch_on 开/关
   * @return int 
   */
  int inturn(bool switch_on);

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
   * @brief 添加数据观察者
   * 
   * @param obs 
   */
  void attach(std::shared_ptr<calibrate_obs> obs);

  /**
   * @brief 移除数据观察者
   * 
   * @param obs 
   */
  void detach(std::shared_ptr<calibrate_obs> obs);

 private:
 /**
  * @brief 数据抛出
  * 
  * @param ua 上相机反射数据（上光源点亮时）
  * @param db 下相机透射数据（上光源点亮时）
  * @param da 上相机透射数据（下光源点亮时）
  * @param ub 下相机反射数据（下光源点亮时）
  */
  void notify_frame(
      state s,
      std::shared_ptr<camera::frame> ua,
      std::shared_ptr<camera::frame> db,
      std::shared_ptr<camera::frame> da,
      std::shared_ptr<camera::frame> ub);

  /**
   * @brief 触发相机取数据
   * 
   */
  void grab_dcdf(state s);

  /**
   * @brief 控制板状态回调函数
   * 
   * @param s 
   */
  void board_status(std::uint32_t s);

 private:
  bool m_run;
  bool m_ulight;
  bool m_dlight;
  bool m_inturn;
  bool m_busy;
  std::shared_ptr<camera::camera> m_ucam;
  std::shared_ptr<camera::camera> m_dcam;
  std::shared_ptr<board::board> m_board;

  std::uint32_t m_ca_ret = 223;
  std::uint32_t m_ca_tet = 350;
  std::uint32_t m_cb_ret = 322;
  std::uint32_t m_cb_tet = 400;

  boost::asio::thread_pool m_executor;

  std::shared_ptr<cal_board> m_board_obs;
  std::list<std::shared_ptr<calibrate_obs>> m_observers;

  std::string m_grain_type;
  std::string m_abnormal_type;
  std::uint32_t m_cur_id;
};

}  // namespace calibrate

#endif  // CALIBRATE_CALIBRATE_H_
