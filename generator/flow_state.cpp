/**
 * @file flow_state.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost/asio.hpp>
#include <boost/asio/post.hpp>

#include "generator/flow_state.h"
#include "generator/flow_control.h"
#include "module/camera/common.h"
#include "logging/log.h"
const float img_rate = 2.0;
const int top_line = 145;

boost::log::sources::severity_logger<logging::severity_level> fs_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(fs_lg, "Module", "FC");

namespace generator {

flow_start::flow_start(std::uint32_t timeout_seconds, std::weak_ptr<flow_control> w)
    : m_timeout_remain(timeout_seconds * 1000),
      m_sem_run(0),
      m_sem_bd(0),
      m_worker(std::move(w)) {
  m_tworker = std::thread(&flow_start::worker, this);
}

flow_start::~flow_start() {
  m_worker_stop = true;
  m_active = false;
  m_run_from_pause = false;
  // m_cond_bd.notify_all();
  m_sem_bd.post();
  // m_cond_run.notify_all();
  m_sem_run.post();
  if (m_tworker.joinable()) m_tworker.join();
}

void flow_start::run() {
  if (m_active) return;
  // m_cond_run.notify_all();
  m_sem_run.post();
}

void flow_start::board_status(std::uint32_t s) {
  // 处理控制板的运行信号
  if (BOARD_STATUS_RUNNING == s) {
    // m_cond_bd.notify_all();
    m_sem_bd.post();
  }
}

void flow_start::pause() {
  m_active = false;
  // m_cond_bd.notify_all();
  m_sem_bd.post();
  m_run_from_pause = true;
}

void flow_start::stop() {
  m_active = false;
  // m_cond_bd.notify_all();
  m_sem_bd.post();
  m_run_from_pause = false;
}

/**
 * @brief 状态worker
 * 
 */
void flow_start::worker() {
  auto w = m_worker.lock();
  if (!w) {
    BOOST_LOG_SEV(fs_lg, logging::MAJOR) << "thread flow_start: get fc worker failed";
    return;
  }

  while (!m_worker_stop) {
    BOOST_LOG_SEV(fs_lg, logging::INFO) << "thread flow_start: waiting for active";
    // 等待worker active
    // std::unique_lock<std::mutex> lk(m_mutex_run);
    // m_cond_run.wait(lk);
    m_sem_run.wait();
    if (m_worker_stop) break;
    if (m_active) continue;
    m_active = true;
    BOOST_LOG_SEV(fs_lg, logging::INFO) << "thread flow_start: active";
    if (!m_run_from_pause) {
      // 判断料仓是否有余料
      std::pair<bool, bool> policy = w->flow_policy();
      // 料仓有余料，结束
      if (policy.first || policy.second) {
        w->notify(notify_code::remain_sample);
        m_active = false;
        continue;
      }
      // 料仓正常
      w->notify(notify_code::pre_start);
      // 等待下位机运行信号
      // std::unique_lock<std::mutex> bd_lk(m_mutex_bd);
      // m_cond_bd.wait(bd_lk);
      m_sem_bd.wait();
      // 重置开始等待时间
      m_timeout_remain = w->start_seconds() * 1000;
    }

    while (m_active) {
      auto timer_start = std::chrono::high_resolution_clock::now();
      if (w->flow_policy().first) {
        BOOST_LOG_SEV(fs_lg, logging::INFO) << "change state start -> loop";
        // 进入 loop 状态
        w->set_state(fc_state::loop);
        w->run();
        w->notify(notify_code::start);
        // 重置状态
        m_active = false;
        m_run_from_pause = false;
        break;
      }

      // 等待100毫秒，即一秒钟取10帧数据
      std::unique_lock<std::mutex> lk_timer(m_mutex_timer);
      m_cond_timer.wait_for(lk_timer, std::chrono::milliseconds(100));
      auto timer_test = std::chrono::high_resolution_clock::now();
      auto exec_time = std::chrono::duration_cast<std::chrono::milliseconds>(
          timer_test - timer_start).count();
      // 更新剩余时间
      m_timeout_remain -= exec_time;
      if (m_timeout_remain <= 0) {
        // 异常：料仓没有样本
        w->notify(notify_code::no_sample);
        // 重置状态
        m_timeout_remain = w->start_seconds() * 1000;
        m_active = false;
        m_run_from_pause = false;
        break;
      }
    }
  }
}

flow_loop::flow_loop(std::weak_ptr<flow_control> w)
    : m_sem_run(0), m_sem_bd(0), m_worker(std::move(w)) {
  m_tworker = std::thread(&flow_loop::worker, this);
}

flow_loop::~flow_loop() {
  m_worker_stop = true;
  m_active = false;
  // m_cond_bd.notify_all();
  m_sem_bd.post();
  // m_cond_run.notify_all();
  m_sem_run.post();
  if (m_tworker.joinable()) m_tworker.join();
}

void flow_loop::run() {
  if (m_active) return;
  // m_cond_run.notify_all();
  m_sem_run.post();
}

void flow_loop::board_status(std::uint32_t s) {
  // 处理控制板的抓图就绪信号
  if (m_active && BOARD_STATUS_GRAB_READY == s) {
    // m_cond_bd.notify_all();
    m_sem_bd.post();
  }
}

void flow_loop::pause() {
  m_active = false;
  // m_cond_bd.notify_all();
  m_sem_bd.post();
}

void flow_loop::stop() {
  pause();
}

void flow_loop::worker() {
  auto w = m_worker.lock();
  if (!w) {
    BOOST_LOG_SEV(fs_lg, logging::MAJOR) << "thread flow_loop: get fc worker failed";
    return;
  }

  while (!m_worker_stop) {
    BOOST_LOG_SEV(fs_lg, logging::INFO) << "thread flow_loop: waiting for active";
    // 等待worker active
    // std::unique_lock<std::mutex> lk(m_mutex_run);
    // m_cond_run.wait(lk);
    m_sem_run.wait();
    if (m_worker_stop) break;
    if (m_active) continue;
    m_active = true;
    BOOST_LOG_SEV(fs_lg, logging::INFO) << "thread flow_loop: active";

    while (m_active) {
      // 等待控制板的抓图就绪信号
      // std::unique_lock<std::mutex> lk(m_mutex_bd);
      // m_cond_bd.wait(lk);
      m_sem_bd.wait();
      if (!m_active) break;

      std::pair<bool, bool> policy = w->flow_policy();
      // 检测区域一，没有物料，进入停止逻辑
      if (!policy.first) {
        BOOST_LOG_SEV(fs_lg, logging::INFO) << "change fc state loop -> stop";
        w->set_state(fc_state::stop);
        w->run();
        w->notify(notify_code::loop_finish);
        m_active = false;
        break;
      }
    }
  }
}

flow_stop::flow_stop(std::uint32_t stop_sec, std::weak_ptr<flow_control> w)
  : m_seconds(stop_sec), m_sem_run(0), m_sem_bd(0), m_worker(std::move(w)) {
  m_tworker = std::thread(&flow_stop::worker, this);
}

flow_stop::~flow_stop() {
  m_active = false;
  m_worker_stop = true;
  // m_cond_bd.notify_all();
  m_sem_bd.post();
  // m_cond_run.notify_all();
  m_sem_run.post();
  if (m_tworker.joinable()) m_tworker.join();
}

void flow_stop::run() {
  if (m_active) return;
  // m_cond_run.notify_all();
  m_sem_run.post();
}

void flow_stop::worker() {
  auto w = m_worker.lock();
  if (!w) {
    BOOST_LOG_SEV(fs_lg, logging::MAJOR) << "thread flow_stop: get fc worker failed";
    return;
  }

  while (!m_worker_stop) {
    BOOST_LOG_SEV(fs_lg, logging::INFO) << "thread flow_stop: waiting for active";
    // 等待worker active
    // std::unique_lock<std::mutex> lk(m_mutex_run);
    // m_cond_run.wait(lk);
    m_sem_run.wait();
    if (m_worker_stop) break;
    if (m_active) continue;
    m_active = true;
    BOOST_LOG_SEV(fs_lg, logging::INFO) << "thread flow_stop: active";

    if (!m_run_from_pause) {
      // 等待下位机运行信号
      // std::unique_lock<std::mutex> bd_lk(m_mutex_bd);
      // m_cond_bd.wait(bd_lk);
      m_sem_bd.wait();
      // m_seconds = w->stop_seconds();
    }

    // while (m_active) {
    //   if (0 == m_seconds--) {
    //     w->notify(notify_code::stop);
    //     w->set_state(fc_state::start);
    //     m_active = false;
    //     m_run_from_pause = false;
    //     break;
    //   }
    //   std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    if (!m_active) break;
    w->notify(notify_code::stop);
    w->set_state(fc_state::start);
    m_active = false;
    m_run_from_pause = false;

  }
}

void flow_stop::board_status(std::uint32_t s) {
  // 下位机倒计时结束
  if (VIBRATOR_STATUS_READY == s) {
    // m_cond_bd.notify_all();
    m_sem_bd.post();
  }
}

void flow_stop::pause() {
  m_active = false;
  m_run_from_pause = true;
}

void flow_stop::stop() {
  m_active = false;
  m_run_from_pause = false;
}

}  // namespace generator
