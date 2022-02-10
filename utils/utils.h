/**
 * @file utils.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

#include <string>

namespace utils {

class common {
 public:
  ~common();
  common(const common&) = delete;
  common& operator=(const common&) = delete;

  static common* instance();
  void set_camera_plugin_path(const std::string path);
  void set_board_plugin_path(const std::string path);
  void set_algorithm_plugin_path(const std::string path);
  std::string camera_plugin_path() const {return m_cam_path;}
  std::string board_plugin_path() const {return m_board_path;}
  std::string algorithm_plugin_path() const {return m_algorithm_path;}

 private:
  common();

 private:
  std::string m_cam_path;
  std::string m_board_path;
  std::string m_algorithm_path;
};

}  // namespace utils

#endif  // UTILS_UTILS_H_
