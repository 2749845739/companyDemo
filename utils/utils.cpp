/**
 * @file utils.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "utils/utils.h"
#include <utility>

namespace utils {

/// 相机插件目录
#define CAMERA_PLUGIN_PATH "camera_plugin"
/// 控制板插件路径
#define BOARD_PLUGIN_PATH "board_plugin"
/// 算法插件目录
#define ALG_PLUGIN_PATH "graineval_plugin"

common::common()
    : m_cam_path(CAMERA_PLUGIN_PATH),
    m_board_path(BOARD_PLUGIN_PATH),
    m_algorithm_path(ALG_PLUGIN_PATH) {}

common::~common() {}

common* common::instance() {
  static common ins;
  return &ins;
}

void common::set_camera_plugin_path(const std::string path) {
  m_cam_path = path;
}
void common::set_board_plugin_path(const std::string path) {
  m_board_path = path;
}

void common::set_algorithm_plugin_path(const std::string path) {
  m_algorithm_path = path;
}

}  // namespace utils
