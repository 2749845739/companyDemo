/**
 * @file flow_control.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 样本流量监控(flow control)，该模块监控控制板送料信息，给控制板发送入料指令
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef GENERATOR_FLOW_CONTROL_H_
#define GENERATOR_FLOW_CONTROL_H_

#include <condition_variable>
#include <memory>
#include <unordered_map>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/core/noncopyable.hpp>

#include "generator/flow_state.h"
#include "module/camera/common.h"
#include "module/camera/camera.h"
#include "module/board/board.h"

#include "opencv2/opencv.hpp"

namespace generator {

enum class notify_code : std::uint8_t {
  pre_start,      // 开始逻辑启动
  remain_sample,  // 有余料
  no_sample,      // 没有物料
  start,          // 开始逻辑结束（开始送料），进入循环逻辑
  loop_finish,    // 循环逻辑结束，进入停止逻辑
  stop,           // 停止逻辑开始送料
};

class fc_status_observer {
 public:
  virtual void handle_fc_status(notify_code s) = 0;
};

class flow_board;
class flow_control
  : public std::enable_shared_from_this<flow_control>,
    private boost::noncopyable {
 public:
  /**
   * @brief Construct a new flow control object
   * 
   * @param cam 
   * @param bd 
   * @param init_im_path 
   * @param start_line 
   * @param stop_line 
   * @param target_size 
   * @param start_sec 
   * @param stop_sec 
   */
  explicit flow_control(
    std::shared_ptr<camera::camera> cam,
    std::shared_ptr<board::board> bd,
    std::string init_im_path,
    std::uint32_t start_line,
    std::uint32_t stop_line,
    std::uint32_t target_size,
    std::uint32_t start_sec,
    std::uint32_t stop_sec);

  /**
   * @brief Destroy the flow control object
   * 
   */
  ~flow_control();

  /**
   * @brief 
   * 
   */
  void init_state();

  /**
   * @brief 开始当前状态
   * 
   */
  void run();

  /**
   * @brief 暂停
   * 
   */
  void pause();

  /**
   * @brief 停止
   * 
   */
  void stop();

  /**
   * @brief 根据policy发送流量相机的状态
   * 
   * @param policy 
   */
  void deliver_fc_status(std::pair<bool, bool> policy);

  /**
   * @brief 设置当前flow控制的状态
   * 
   * @param state 
   */
  void set_state(fc_state state);

  /**
   * @brief  设置开始逻辑，帧数上限
   * 
   * @param count 
   */
  void start_seconds(std::uint32_t sec) {m_start_sec = sec;}

  /**
   * @brief 获取开始逻辑，帧数上限（一秒10帧）
   * 
   * @return std::uint32_t 
   */
  std::uint32_t start_seconds() const {return m_start_sec;}

  /**
   * @brief 设置停止逻辑持续时间
   * 
   * @return std::uint32_t 
   */
  void stop_seconds(std::uint32_t sec); // {m_stop_sec = sec;}

  /**
   * @brief 获取停止逻辑持续时间
   * 
   * @return std::uint32_t 
   */
  std::uint32_t stop_seconds() const {return m_stop_sec;}

  /**
   * @brief 设置起始线位置
   * 
   * @param pixels 起始线距离图像边缘的像素数
   */
  void start_line(std::uint32_t pixels);  // {m_start_line = pixels;}

  /**
   * @brief 获取起始线位置
   * 
   * @return std::uint32_t 起始线距离图像边缘的像素数
   */
  std::uint32_t start_line() const {return m_start_line;}

  /**
   * @brief 设置结束线位置
   * 
   * @param pixels 结束线距离图像边缘的像素数
   */
  void stop_line(std::uint32_t pixels);  // {m_stop_line = pixels;}

  /**
   * @brief 获取结束线位置
   * 
   * @return std::uint32_t 结束线距离图像边缘的像素数
   */
  std::uint32_t stop_line() const {return m_stop_line;}

  /**
   * @brief 设置检测区域大小
   * 
   * @param pixels 检测区域像素数
   */
  void target_size(std::uint32_t pixels);  // {m_target_size = pixels;}

  /**
   * @brief 获取检测区域大小
   * 
   * @param std::uint32_t 检测区域像素数
   */
  std::uint32_t target_size() const {return m_target_size;}

  /**
   * @brief flow控制的状态策略
   * first item：开始区域是否存在物料
   * second item：结束区域是否存在物料
   * 
   * @return std::pair<bool, bool> 
   */
  std::pair<bool, bool> flow_policy();

  /**
   * @brief 抓取一帧数据，更新模板图像
   * 
   */
  void update_template();

  /**
   * @brief 状态通知处理函数
   * 
   * @param nc 
   */
  void notify(notify_code nc);

  /**
   * @brief 添加fc控制的状态观察者
   *
   * @param obs
   */
  void attach(std::shared_ptr<fc_status_observer> obs);

  /**
   * @brief 取出fc控制的状态观察者
   *
   * @param obs
   */
  void detach(std::shared_ptr<fc_status_observer> obs);

 private:
  /**
   * @brief Get the frame object
   * 
   * @return cv::Mat 
   */
  cv::Mat get_frame();

  /**
   * @brief 计算阈值
   * 
   * @param im 图像
   * @return std::vector<int> 
   */
  std::vector<int> compute_thresh(cv::Mat im);

  /**
   * @brief 对监控相机的图像进行预处理
   * 
   * @param im 
   * @return cv::Mat 
   */
  cv::Mat preprocess(cv::Mat im);

  /**
   * @brief 处理控制板的数据帧
   * 
   * @param f 
   */
  void handle_board_frame(board::frame f);

  /**
   * @brief 处理控制板状态函数
   * 
   * @param s 
   */
  void handle_board_status(std::uint32_t s);

 public:
  /// 状态执行线程池
  boost::asio::thread_pool m_state_executor;

 private:
  bool m_pause;
  std::shared_ptr<camera::camera> m_camera;
  std::shared_ptr<board::board> m_board;
  std::string m_init_im_path;
  cv::Mat m_init_im;
  std::vector<int> m_init_mean;
  std::uint32_t m_start_line;
  std::uint32_t m_stop_line;
  std::uint32_t m_target_size;
  fc_state m_current_state;
  std::uint32_t m_start_sec;
  std::uint32_t m_stop_sec;
  std::shared_ptr<flow_board> m_flow_board;
  std::uint32_t m_im_id;
  std::string m_stime;
  // 用于强制结束逻辑
  std::mutex m_mutex_stop;
  std::condition_variable m_cond_stop;
  // 更改目标区域 - 锁
  std::mutex m_mutex_tsize;
  cv::Mat m_template_im;
  std::list<std::shared_ptr<fc_status_observer>> m_observers;
  std::unordered_map<fc_state, std::shared_ptr<flow_state>> m_states;
};

}  // namespace generator

#endif  // GENERATOR_FLOW_CONTROL_H_
