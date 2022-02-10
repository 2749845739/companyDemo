/**
 * @file driver.h
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODULE_CAMERA_DRIVER_H_
#define MODULE_CAMERA_DRIVER_H_

#include <string>
#include <list>
#include <unordered_map>
#include <vector>
#include <memory>

#include "module/camera/camera.h"

namespace camera {

/**
 * @brief 相机组件观察者接口类
 * 
 */
class component_observer {
 public:
  virtual void notify_detect(std::shared_ptr<camera> cam) = 0;
  virtual void notify_remove(std::shared_ptr<camera> cam) = 0;
};

/**
 * @brief 相机组件观察者管理类
 * 
 */
class component_subject {
 public:
  virtual ~component_subject() {
    m_observers.clear();
  }

  void attach(std::shared_ptr<component_observer> obs) {
    for (const auto &it : m_observers) if (it == obs) return;
    m_observers.push_back(obs);
  }

  void detach(std::shared_ptr<component_observer> obs) {
    m_observers.remove(obs);
  }

 protected:
  void update(bool detected, std::shared_ptr<camera> camera) {
    if (detected) {  // 检测到新相机组件
      for (auto& obs : m_observers) {
        obs->notify_detect(camera);
      }
    } else {  // 相机组件被移除
      for (auto& obs : m_observers) {
        obs->notify_remove(camera);
      }
    }
  }

 private:
  std::list<std::shared_ptr<component_observer>> m_observers;
};

class driver : public component_subject {
 public:
  ~driver();
  driver(const driver&) = delete;
  driver& operator=(const driver&) = delete;

  /**
   * @brief 获取实例
   * 
   * @return driver& 单一实例
   */
  static driver* instance();

  /**
   * @brief 扫描相机，并更新相机列表
   * 
   */
  const std::unordered_map<std::string, std::shared_ptr<camera>> scan_camera();

  /**
   * @brief 获取相机列表
   * 
   * @return const std::unordered_map<std::string, std::shared_ptr<camera>> 
   */
  const std::unordered_map<std::string, std::shared_ptr<camera>> all_camera() const;

  /**
   * @brief 添加相机
   * 
   * @param cam 
   * @return int 0表示成功添加
   */
  int add_camera(const std::string uid, std::shared_ptr<camera> cam);

  /**
   * @brief 移除相机
   * 
   * @return int 0表示操作成功
   */
  int remove_camera(const std::string uid);

 private:
  /**
   * @brief Construct a new driver object
   * 
   * @param i 
   */
  driver();

  /**
   * @brief 
   * 
   * @param uid 相机UUID
   * @param frame 相机frame数据
   * @param puser 用户数据
   */
  void frame_callback(std::string uid, GCamera::FrameInfo fdata, void* puser);

 private:
  typedef boost::shared_ptr<GCamera::CameraApi>(create_t)();
  /// 相机列表
  std::unordered_map<std::string, std::shared_ptr<camera>> m_cameras;
  /// 插件动态库名（basename）
  std::vector<std::string> m_lib_names;
  /// 所有插件库
  std::vector<boost::shared_ptr<GCamera::CameraApi>> m_libs;
  /// 插件文件 -> lib
  boost::dll::shared_library m_lib;
};

}  // namespace camera

#endif  // MODULE_CAMERA_DRIVER_H_
