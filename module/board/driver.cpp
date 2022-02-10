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

#include <exception>
#include <iostream>
#include <utility>

#include "module/board/driver.h"
#include "utils/utils.h"

#include <boost/dll/import.hpp>
#include <boost/function.hpp>

namespace board {

/// P600控制板插件库名称
#define P600_PLUGIN_LIB "p600_plugin"

// 所有插件库以宏定义，并在构造是初始化完成
driver::driver() : m_lib_names{P600_PLUGIN_LIB} {
  // 插件库查找及初始化需要放在构造函数中，然后会出现无法析构的情况（原因未知）
  for (const auto& lib_name : m_lib_names) {
    auto lib_path = boost::dll::fs::path(utils::common::instance()->board_plugin_path()) / lib_name;
    try {
      m_lib = boost::dll::shared_library(lib_path, boost::dll::load_mode::append_decorations);
      if (!m_lib.has(BOARD_CREATOR_SYMBOL)) continue;
      boost::shared_ptr<GBoard::board_plugin_api> plib =
        boost::dll::import_alias<create_t>(boost::move(m_lib), BOARD_CREATOR_SYMBOL)();
      // 插件status回调函数设置
      plib->set_status_callback(std::bind(&driver::status_callback, this,
          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), nullptr);
      // 插件frame回调函数设置
      plib->set_data_callback(std::bind(&driver::frame_callback, this,
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
  // for (auto it : m_boards) {
  //   remove_board(it.first);
  // }
  if (m_lib.is_loaded()) {
    m_lib.unload();
  }
}

driver* driver::instance() {
  static driver ins;
  return &ins;
}

const std::unordered_map<std::string, std::shared_ptr<board>> driver::scan_board() {
  for (auto& plib : m_libs) {
    // 插件，控制板列表(uid)
    std::shared_ptr<std::vector<std::string>> pboards(new std::vector<std::string>);
    if (GBoard::board_error_t::success != plib->enum_board(pboards)) {
      continue;
    }

    for (auto uid : *pboards) {
      // 尝试连接控制板
      if (GBoard::board_error_t::success != plib->connect_board(uid)) {
        continue;
      }
      // 控制板已经存在，则跳过
      if (m_boards.end() != m_boards.find(uid)) continue;
      std::shared_ptr<board> pcomp(new board(uid, plib));
      m_boards[uid] = pcomp;
      // 通知添加控制板组件
      update(true, pcomp);
      // 如果有多个控制板，这里break需要处理
      break;
    }
  }
  return m_boards;
}

void driver::frame_callback(
    std::string uid, GBoard::board_frame fdata, void* puser) {
  auto board_iter = m_boards.find(uid);
  if (board_iter == m_boards.end()) return;
  if (fdata.name == GBoard::board_frame::weightor) {
    // 将uint32转为float，并将mg转为g
    float wei = *(reinterpret_cast<float*>(&(fdata.value))) / 1000;
    // 如果质量小于0，则置0
    if (wei < 0.f) wei = 0.f;
    board_iter->second->notify_frame({wei});
  }
}

void driver::status_callback(
    std::string uid, GBoard::component_status_t status, void* puser) {
  auto board_iter = m_boards.find(uid);
  if (board_iter == m_boards.end()) return;
  board_iter->second->notify_status(status.name << 16 | status.status);
}

const std::unordered_map<std::string, std::shared_ptr<board>> driver::all_board() const {
  return m_boards;
}

int driver::add_board(const std::string uid, std::shared_ptr<board> comp) {
  // 控制板uid冲突
  if (m_boards.end() != m_boards.find(uid)) return 1;
  m_boards[uid] = comp;
  // 通知添加新控制板组件
  update(true, comp);
  return 0;
}

int driver::remove_board(const std::string uid) {
  auto iter = m_boards.find(uid);
  // 未找到控制板
  if (m_boards.end() == iter) return 1;
  m_boards.erase(iter);
  // 通知移除控制板组件
  update(false, iter->second);
  return 0;
}

}  // namespace board
