/**
 * @file flow_control.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <exception>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <opencv2/imgcodecs.hpp>

#include "generator/flow_control.h"
#include "generator/flow_state.h"
#include "module/board/board.h"
#include "logging/log.h"

const float thre_rate = 1.5;
const int top_line = 145;


namespace generator {

boost::log::sources::severity_logger<logging::severity_level> fc_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(fc_lg, "Module", "FC");

class flow_board : public board::board_observer {
 public:
  explicit flow_board(std::string uid,
      std::function<void(board::frame)> frame_cb,
      std::function<void(std::uint32_t)> status_cb)
      : m_uid(uid), m_frame_cb(frame_cb), m_status_cb(status_cb) {}

  /**
 * @brief 处理控制板frame
 * 
 * @param uid 控制板序号
 * @param frame 控制板frame数据
 */
  void handle_frame(std::string uid, board::frame frame) {
    if (m_uid == uid && m_frame_cb) {
      m_frame_cb(frame);
    }
  }

  /**
   * @brief 处理控制板状态
   * 
   * @param uid 控制板序号
   * @param status 状态值
   */
  void handle_status(std::string uid, std::uint32_t status) {
    if (m_uid == uid && m_status_cb) {
      m_status_cb(status);
    }
  }

 private:
  std::string m_uid;
  std::function<void(board::frame)> m_frame_cb;
  std::function<void(std::uint32_t)> m_status_cb;
};

flow_control::flow_control(std::shared_ptr<camera::camera> cam,
    std::shared_ptr<board::board> bd,
    std::string init_im_path,
    std::uint32_t start_line,
    std::uint32_t stop_line,
    std::uint32_t target_size,
    std::uint32_t start_sec,
    std::uint32_t stop_sec)
    : m_pause(false),
    m_camera(cam),
    m_board(bd),
    m_init_im_path(init_im_path),
    m_start_line(start_line),
    m_stop_line(stop_line),
    m_target_size(target_size),
    m_start_sec(start_sec),
    m_stop_sec(stop_sec),
    m_im_id(0),
    m_stime() {
  // 开始相机
  m_camera->start();
  set_state(fc_state::start);
  m_flow_board = std::make_shared<flow_board>(m_board->uid(),
    std::bind(&flow_control::handle_board_frame, this, std::placeholders::_1),
    std::bind(&flow_control::handle_board_status, this, std::placeholders::_1));
  m_board->attach(m_flow_board);

  try {
    // 读取模板图像
    m_template_im = cv::imread(m_init_im_path, cv::IMREAD_COLOR);
    if (!m_template_im.data) {
      BOOST_LOG_SEV(fc_lg, logging::MINOR) << "invalid fc template image";
      update_template();
    } else {
      // 获取模板图像
      m_init_im = preprocess(m_template_im);
      // 计算模块图像均值
      m_init_mean = compute_thresh(m_init_im);
      m_init_mean[0] *= thre_rate;
      m_init_mean[1] *= thre_rate;
      BOOST_LOG_SEV(fc_lg, logging::INFO) << "construct m_init_mean: ["
        << m_init_mean[0] << ", " << m_init_mean[1] << "]";
    }
  } catch (std::exception e) {
    BOOST_LOG_SEV(fc_lg, logging::MINOR) << "invalid fc template image path";
    update_template();
  }
  // 这里需要将时间下发到下位机
  stop_seconds(m_stop_sec);
}

flow_control::~flow_control() {
  m_observers.clear();
  // 停止相机
  m_camera->stop();
  m_board->detach(m_flow_board);
  m_cond_stop.notify_all();
}

void flow_control::init_state() {
  m_states[fc_state::start] = std::make_shared<flow_start>(
    m_start_sec, std::weak_ptr<flow_control>(shared_from_this()));

  m_states[fc_state::loop] = std::make_shared<flow_loop>(
    std::weak_ptr<flow_control>(shared_from_this()));

  m_states[fc_state::stop] = std::make_shared<flow_stop>(
    m_stop_sec, std::weak_ptr<flow_control>(shared_from_this()));
}

void flow_control::run() {
  if (board::e_task::unsound != m_board->task()) {
    m_board->task(board::e_task::unsound);
  }
  auto curr = m_states[m_current_state];
  if (curr) curr->run();
  if (m_pause) m_board->start_task();
  m_pause = false;
}

void flow_control::pause() {
  m_board->pasue_task();
  auto curr = m_states[m_current_state];
  if (curr) curr->pause();
  m_pause = true;
}

void flow_control::stop() {
  BOOST_LOG_SEV(fc_lg, logging::INFO) << "enter force stop: ";
  auto curr = m_states[m_current_state];
  if (curr) curr->stop();
  // 用于下一轮检测
  set_state(fc_state::start);
  // 防止暂停状态下 点击结束按钮
  m_pause = false;
  // 下位机将流量相机状态指令 作为强制停止的开始标志
  std::pair<bool, bool> cur_policy = this->flow_policy();
  deliver_fc_status(cur_policy);

  // 谷道上无料，后续不需要上位机的参与
  if (!cur_policy.first && !cur_policy.second) return;
  boost::asio::post(m_state_executor, [this, &cur_policy] {
    std::unique_lock<std::mutex> lk(m_mutex_stop);
    m_cond_stop.wait(lk);
    while (true) {
      cur_policy = this->flow_policy();
      // 振动器振动，直到流量相机-状态空
      if (!cur_policy.first && !cur_policy.second) {
        deliver_fc_status(cur_policy);
        break;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  });
}

/**
 * @brief 根据policy发送流量相机的状态信息
 * 
 * @param policy 
 */
void flow_control::deliver_fc_status(std::pair<bool, bool> policy) {
  if (!policy.first && !policy.second) {         // 区域1，区域2都没料
    m_board->fc_status(10);
  } else if (!policy.first && policy.second)  {  // 区域1没料，区域2有料
    m_board->fc_status(11);
  } else if (policy.first && policy.second)   {  // 区域1，区域2都有料
    m_board->fc_status(12);
  } else if (policy.first && !policy.second) {   // 区域1有料，区域2没料
    m_board->fc_status(13);
  }
}

/**
 * @brief 设置当前状态
 * 
 * @param state 
 */
void flow_control::set_state(fc_state state) {
  m_current_state = state;
  // 重置图像序号
  if (m_current_state == fc_state::start) {
    m_im_id = 0;
    std::time_t tcur = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char time_str[32] = {0};
    std::strftime(time_str, sizeof(time_str), "%Y%m%dT%H%M%S", std::localtime(&tcur));
    m_stime = std::string(time_str);
  }
}


/**
 * @brief 设置停止逻辑持续时间
 * 
 * @return std::uint32_t 
 */
void flow_control::stop_seconds(std::uint32_t sec) {
  m_board->vibrator_clear_time(0, sec);
  m_stop_sec = sec;
}



/**
 * @brief 设置起始线位置
 * 
 * @param pixels 起始线距离图像边缘的像素数
 */
void flow_control::start_line(std::uint32_t pixels) {
  if (m_start_line == pixels) return;
  std::lock_guard<std::mutex> lk(m_mutex_tsize);
  m_start_line = pixels;
  // 更新模板数据
  m_init_im = preprocess(m_template_im);
  m_init_mean = compute_thresh(m_init_im);
  m_init_mean[0] *= thre_rate;
  m_init_mean[1] *= thre_rate;
  BOOST_LOG_SEV(fc_lg, logging::INFO) << "start_line changed m_init_mean: ["
    << m_init_mean[0] << ", " << m_init_mean[1] << "]";
}

/**
 * @brief 设置结束线位置
 * 
 * @param pixels 结束线距离图像边缘的像素数
 */
void flow_control::stop_line(std::uint32_t pixels) {
  if (m_stop_line == pixels) return;
  std::lock_guard<std::mutex> lk(m_mutex_tsize);
  m_stop_line = pixels;
  // 更新模板数据
  m_init_im = preprocess(m_template_im);
  m_init_mean = compute_thresh(m_init_im);
  m_init_mean[0] *= thre_rate;
  m_init_mean[1] *= thre_rate;
  BOOST_LOG_SEV(fc_lg, logging::INFO) << "stop_line changed m_init_mean: ["
    << m_init_mean[0] << ", " << m_init_mean[1] << "]";
}

/**
 * @brief 设置检测区域大小
 * 
 * @param pixels 检测区域像素数
 */
void flow_control::target_size(std::uint32_t pixels) {
  if (m_target_size == pixels) return;
  std::lock_guard<std::mutex> lk(m_mutex_tsize);
  m_target_size = pixels;
  // 更新模板数据
  m_init_im = preprocess(m_template_im);
  m_init_mean = compute_thresh(m_init_im);
  m_init_mean[0] *= thre_rate;
  m_init_mean[1] *= thre_rate;
  BOOST_LOG_SEV(fc_lg, logging::INFO) << "target_size changed m_init_mean: ["
    << m_init_mean[0] << ", " << m_init_mean[1] << "]";
}

std::pair<bool, bool> flow_control::flow_policy() {
  std::vector<int> curr_mean;
  {
    std::lock_guard<std::mutex> lk(m_mutex_tsize);
    // cv::Mat diff_im;
    // cv::Mat curr_im = preprocess(get_frame());
    // cv::absdiff(m_init_im, curr_im, diff_im);
    // curr_mean = compute_thresh(diff_im);
    cv::Mat curr_im = preprocess(get_frame());
    curr_mean = compute_thresh(curr_im);
  }
  BOOST_LOG_SEV(fc_lg, logging::DATA) << "mean: init vs current ["
    << m_init_mean[0] << ", " << m_init_mean[1]
    << "] vs [" << curr_mean[0] << ", " << curr_mean[1] << "]";
  // area 0
  bool area0 = false;
  if (curr_mean[0] >= m_init_mean[0]) {
    area0 = true;
  }
  // area 1
  bool area1 = false;
  if (curr_mean[1] >= m_init_mean[1]) {
    area1 = true;
  }
  return std::make_pair(area0, area1);
}

void flow_control::update_template() {
  {
    std::lock_guard<std::mutex> lk(m_mutex_tsize);
    m_template_im = get_frame();
    m_init_im = preprocess(m_template_im);
    m_init_mean = compute_thresh(m_init_im);
    m_init_mean[0] *= thre_rate;
    m_init_mean[1] *= thre_rate;
    BOOST_LOG_SEV(fc_lg, logging::INFO) << "update_template m_init_mean: ["
      << m_init_mean[0] << ", " << m_init_mean[1] << "]";
  }
  // update template image
  cv::imwrite(m_init_im_path, m_template_im);
}

void flow_control::notify(notify_code nc) {
  BOOST_LOG_SEV(fc_lg, logging::INFO) << "flow state notify: " << static_cast<int>(nc);
  for (const auto &it : m_observers) {
    it->handle_fc_status(nc);
  }
  switch (nc) {
  case notify_code::pre_start:
  m_board->start_task();
  break;
  case notify_code::remain_sample:
  break;
  case notify_code::no_sample:
  m_board->vibrator_sample_exception(0, 0);
  break;
  case notify_code::start:
  m_board->vibrator_sample_ready(0, 0);
  break;
  case notify_code::loop_finish:
  m_board->stop_task();
  break;
  case notify_code::stop:
  // m_board->vibrator_sample_ready(0, 1);
  break;
  default:
  break;
  }
}

void flow_control::attach(std::shared_ptr<fc_status_observer> obs) {
  for (const auto &it : m_observers) if (it == obs) return;
  m_observers.push_back(obs);
}

void flow_control::detach(std::shared_ptr<fc_status_observer> obs) {
  m_observers.remove(obs);
}

cv::Mat flow_control::get_frame() {
  camera::frame frame;
  while (true) {
    int ret = m_camera->get_frame(&frame);
    if (0 == ret) {
      break;
    } else {
      BOOST_LOG_SEV(fc_lg, logging::MINOR) << "get frame failed of " << ret;
    }
  }
  cv::Mat ret_mat(frame.h, frame.w, CV_8UC3, frame.data.get());
#ifdef SAVE_FC_IM
  if (m_current_state == fc_state::loop) {
    std::string sv_name = "fc_im/" + m_stime + "_" + std::to_string(m_im_id) + ".png";
    cv::imwrite(sv_name, ret_mat);
    m_im_id++;
  }
#endif  // SAVE_FC_IM
  return ret_mat.clone();
}

std::vector<int> flow_control::compute_thresh(cv::Mat im) {
  std::vector<int> ret;
  cv::Mat mean_mat;
  cv::Mat std_dev_mat;

  // 计算开始区域的均值
  cv::Mat im_roi_start = im(cv::Rect(0, 0, m_start_line, im.rows));
  cv::meanStdDev(im_roi_start, mean_mat, std_dev_mat);
  ret.push_back(static_cast<int>(mean_mat.at<double>(0, 0)));

  // 计算结束区域的均值
  cv::Mat im_roi_stop = im(cv::Rect(im.cols - m_target_size, 0, m_target_size, im.rows));
  cv::meanStdDev(im_roi_stop, mean_mat, std_dev_mat);
  ret.push_back(static_cast<int>(mean_mat.at<double>(0, 0)));
  return ret;
}

cv::Mat flow_control::preprocess(cv::Mat im) {
  cv::Mat im_roi = im(cv::Rect(m_start_line, top_line, m_stop_line - m_start_line, im.rows - top_line));
  // 颜色转换
  // cv::Mat im_cvt;
  // cv::cvtColor(im_roi, im_cvt, cv::COLOR_BGR2HSV);
  // 通道分离
  std::vector<cv::Mat> im_channles;
  cv::split(im_roi, im_channles);
  // 提取S通道，并去噪
  cv::Mat im_blur;
  cv::blur(im_channles.at(1), im_blur, cv::Size(11, 11));
  return im_blur;
}

void flow_control::handle_board_frame(board::frame f) {
  // 不需要处理控制板数据
}

void flow_control::handle_board_status(std::uint32_t s) {
  if (VIBRATOR_STATUS_RUNNING == s) {
    m_cond_stop.notify_all();
  } else {
    // 将控制板状态信息转到flow的具体流程中
    auto curr = m_states[m_current_state];
    if (curr) curr->board_status(s);
  }
}

}  // namespace generator
