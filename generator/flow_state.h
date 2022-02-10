/**
 * @file flow_state.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GENERATOR_FLOW_STATE_H_
#define GENERATOR_FLOW_STATE_H_

#include <condition_variable>
#include <cstdint>
#include <memory>
#include <mutex>
#include <vector>
#include <utility>
#include <string>

#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "module/camera/camera.h"
#include "module/board/board.h"

namespace generator {

enum fc_state : std::uint8_t {
  start,
  loop,
  stop,
};

class flow_control;
class flow_state {
 public:
  /**
   * @brief 状态执行函数
   * 
   * @param w 状态控制器
   */
  virtual void run() = 0;

  /**
   * @brief 控制板状态回调处理函数
   * 
   * @param s 
   */
  virtual void board_status(std::uint32_t s) = 0;

  /**
   * @brief 暂停
   * 
   */
  virtual void pause() = 0;

  /**
   * @brief 停止
   * 
   */
  virtual void stop() = 0;

  /**
   * @brief worker run by thread
   * 
   */
  virtual void worker() = 0;

 protected:
  bool m_active = false;
  bool m_worker_stop = false;
  bool m_run_from_pause = false;
  // run信号
  // std::mutex m_mutex_run;
  // std::condition_variable m_cond_run;
  // 下位机信号
  // std::mutex m_mutex_bd;
  // std::condition_variable m_cond_bd;
  // worker线程
  std::thread m_tworker;
};

class flow_start : public flow_state {
 public:
  /**
   * @brief 开始，每100ms采集一帧数据，
   * 
   * @param timeout_seconds 检测物料超时时间
   */
  explicit flow_start(std::uint32_t timeout_seconds, std::weak_ptr<flow_control> w);

  /**
   * @brief Destroy the flow start object
   * 
   */
  ~flow_start();

  /**
   * @brief 开始状态执行函数
   * 
   * @param w 控制器
   */
  void run() override;

  /**
   * @brief 控制板状态回调处理函数
   * 
   * @param s 状态值
   */
  void board_status(std::uint32_t s) override;

  /**
   * @brief 暂停
   * 
   */
  void pause() override;

  /**
   * @brief 停止
   * 
   */
  void stop() override;

  void worker() override;

 private:
  /// 超时剩余时间
  std::int64_t m_timeout_remain;
  /// 定时器
  std::mutex m_mutex_timer;
  std::condition_variable m_cond_timer;
  // run信号
  boost::interprocess::interprocess_semaphore m_sem_run;
  // 下位机信号
  boost::interprocess::interprocess_semaphore m_sem_bd;
  const std::weak_ptr<flow_control> m_worker;
};

class flow_loop : public flow_state {
 public:
  /**
   * @brief Construct a new flow loop object
   * 
   */
  explicit flow_loop(std::weak_ptr<flow_control> w);

  /**
   * @brief Destroy the flow loop object
   * 
   */
  ~flow_loop();

  /**
   * @brief 运行状态执行函数
   * 
   * @param w 控制器
   */
  void run() override;

  /**
   * @brief 控制板状态回调处理函数
   * 
   * @param s 状态值
   */
  void board_status(std::uint32_t s) override;

  /**
   * @brief 暂停
   * 
   */
  void pause() override;

  /**
   * @brief 停止
   * 
   */
  void stop() override;

  void worker() override;

 private:
  // run信号
  boost::interprocess::interprocess_semaphore m_sem_run;
  // 下位机信号
  boost::interprocess::interprocess_semaphore m_sem_bd;
  const std::weak_ptr<flow_control> m_worker;
};

class flow_stop : public flow_state {
 public:
  /**
   * @brief Construct a new flow stop object
   * 
   * @param stop_sec 
   * @param w 
   */
  explicit flow_stop(std::uint32_t stop_sec, std::weak_ptr<flow_control> w);

  /**
   * @brief Destroy the flow stop object
   * 
   */
  ~flow_stop();

  /**
   * @brief 停止状态执行函数
   * 
   * @param w 控制器
   */
  void run() override;

  /**
   * @brief 控制板状态回调处理函数
   * 
   * @param s 状态值
   */
  void board_status(std::uint32_t s) override;

  /**
   * @brief 暂停
   * 
   */
  void pause() override;

  /**
   * @brief 停止
   * 
   */
  void stop() override;

  void worker() override;

 private:
  std::uint32_t m_seconds;
  bool m_is_handled;
  // run信号
  boost::interprocess::interprocess_semaphore m_sem_run;
  // 下位机信号
  boost::interprocess::interprocess_semaphore m_sem_bd;
  const std::weak_ptr<flow_control> m_worker;
};

}  // namespace generator

#endif  // GENERATOR_FLOW_STATE_H_
