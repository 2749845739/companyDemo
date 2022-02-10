/**
 * @file driver.h
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODULE_BOARD_DRIVER_H_
#define MODULE_BOARD_DRIVER_H_

#include <string>
#include <list>
#include <unordered_map>
#include <vector>
#include <memory>

#include "module/board/board_plugin_api.hpp"
#include "module/board/board.h"

namespace board {

/**
 * @brief 控制板组件观察者接口类
 * 
 */
class component_observer {
 public:
  virtual void notify_detect(std::shared_ptr<board> comp) = 0;
  virtual void notify_remove(std::shared_ptr<board> comp) = 0;
};

/**
 * @brief 控制板组件观察者管理类
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
  void update(bool detected, std::shared_ptr<board> comp) {
    if (detected) {  // 检测到新相机组件
      for (auto& obs : m_observers) {
        obs->notify_detect(comp);
      }
    } else {  // 相机组件被移除
      for (auto& obs : m_observers) {
        obs->notify_remove(comp);
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
  const std::unordered_map<std::string, std::shared_ptr<board>> scan_board();

  /**
   * @brief 获取相机列表
   * 
   * @return const std::unordered_map<std::string, std::shared_ptr<board>> 
   */
  const std::unordered_map<std::string, std::shared_ptr<board>> all_board() const;

  /**
   * @brief 添加相机
   * 
   * @param cam 
   * @return int 0表示成功添加
   */
  int add_board(const std::string uid, std::shared_ptr<board> comp);

  /**
   * @brief 移除相机
   * 
   * @return int 0表示操作成功
   */
  int remove_board(const std::string uid);

 private:
  /**
   * @brief Construct a new driver object
   * 
   * @param i 
   */
  driver();

  void frame_callback(std::string uid, GBoard::board_frame fdata, void* puser);
  void status_callback(std::string uid, GBoard::component_status_t status, void* puser);

 private:
  typedef boost::shared_ptr<GBoard::board_plugin_api>(create_t)();
  /// 控制板列表
  std::unordered_map<std::string, std::shared_ptr<board>> m_boards;
  /// 插件动态库名（basename）
  std::vector<std::string> m_lib_names;
  /// 所有插件库
  std::vector<boost::shared_ptr<GBoard::board_plugin_api>> m_libs;
  /// 插件文件 -> lib
  boost::dll::shared_library m_lib;
};

}  // namespace board

#endif  // MODULE_BOARD_DRIVER_H_
