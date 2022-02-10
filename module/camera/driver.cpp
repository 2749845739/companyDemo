/**
 * @file driver.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "module/camera/driver.h"
#include "utils/utils.h"

#include <exception>
#include <iostream>
#include <utility>

#include <boost/dll/import.hpp>
#include <boost/function.hpp>

namespace camera {

#define DO3THKING_PLUGIN_LIB "do3think_plugin"

// 所有插件库以宏定义，并在构造是初始化完成
driver::driver() : m_lib_names{DO3THKING_PLUGIN_LIB} {
  // 插件库查找及初始化需要放在构造函数中，然后会出现无法析构的情况（原因未知）
  for (const auto& lib_name : m_lib_names) {
    auto lib_path = boost::dll::fs::path(utils::common::instance()->camera_plugin_path()) / lib_name;
    try {
      m_lib = boost::dll::shared_library(lib_path, boost::dll::load_mode::append_decorations);
      if (!m_lib.has(CAMERA_CREATOR_SYMBOL)) continue;
      boost::shared_ptr<GCamera::CameraApi> plib =
        boost::dll::import_alias<create_t>(boost::move(m_lib), CAMERA_CREATOR_SYMBOL)();
      // 插件frame回调函数设置
      plib->setFrameCB(std::bind(&driver::frame_callback, this,
          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), nullptr);
      // 所有插件库
      m_libs.push_back(plib);
    } catch(std::exception e) {
      // 未找到动态库文件
      continue;
    }
  }
}

driver::~driver() {
  // for (auto it : m_cameras) {
  //   remove_camera(it.first);
  // }
  if (m_lib.is_loaded()) {
    m_lib.unload();
  }
}

driver* driver::instance() {
  static driver ins;
  return &ins;
}

const std::unordered_map<std::string, std::shared_ptr<camera>> driver::scan_camera() {
  for (auto& plib : m_libs) {
    for (auto cid : plib->findCamera()) {
      // 相机已经存在，则跳过
      if (m_cameras.end() != m_cameras.find(cid)) continue;
      std::shared_ptr<camera> pcam(new camera(cid, plib));
      // 相机构造失败（open -> get_info），则跳过
      if (!pcam->is_ready()) continue;
      m_cameras[cid] = pcam;
      // 通知添加新相机组件
      update(true, pcam);
    }
  }
  return m_cameras;
}

void driver::frame_callback(
    std::string uid, GCamera::FrameInfo fdata, void* puser) {
  auto camera_iter = m_cameras.find(uid);
  if (camera_iter == m_cameras.end()) return;
  camera_iter->second->notify_frame({uid, fdata.w, fdata.h, fdata.data});
}

const std::unordered_map<std::string, std::shared_ptr<camera>> driver::all_camera() const {
  return m_cameras;
}

int driver::add_camera(const std::string uid, std::shared_ptr<camera> cam) {
  // 相机uid冲突
  if (m_cameras.end() != m_cameras.find(uid)) return 1;
  m_cameras[uid] = cam;
  // 通知添加新相机组件
  update(true, cam);
  return 0;
}

int driver::remove_camera(const std::string uid) {
  auto iter = m_cameras.find(uid);
  // 未找到相机
  if (m_cameras.end() == iter) return 1;
  m_cameras.erase(iter);
  // 通知移除相机组件
  update(false, iter->second);
  return 0;
}

}  // namespace camera
