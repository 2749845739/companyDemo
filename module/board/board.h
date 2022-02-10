/**
 * @file board.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-09-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODULE_BOARD_BOARD_H_
#define MODULE_BOARD_BOARD_H_

#include <iostream>
#include <string>
#include <memory>
#include <list>
#include <cstdint>
#include <unordered_map>

#include <boost/asio.hpp>

#include "module/board/board_plugin_api.hpp"
// 送料板到达4号位，可以进行图像采集
constexpr std::uint32_t BOARD_STATUS_GRAB_READY =
    GBoard::component_status_t::name_t::board << 16 |
    GBoard::component_status_t::stats_t::grab_ready;
// 控制板收到无效指令
constexpr std::uint32_t BOARD_STATUS_INVALID =
    GBoard::component_status_t::name_t::board << 16 |
    GBoard::component_status_t::stats_t::invalid;
// 控制板进入停止/就绪状态
constexpr std::uint32_t BOARD_STATUS_READY =
    GBoard::component_status_t::name_t::board << 16 |
    GBoard::component_status_t::stats_t::ready;
// 控制板进入运行状态
constexpr std::uint32_t BOARD_STATUS_RUNNING =
    GBoard::component_status_t::name_t::board << 16 |
    GBoard::component_status_t::stats_t::running;
// 控制板进入暂停状态
constexpr std::uint32_t BOARD_STATUS_PAUSE =
    GBoard::component_status_t::name_t::board << 16 |
    GBoard::component_status_t::stats_t::pause;
// 送料板到达0号位，进入停止逻辑
constexpr std::uint32_t BOARD_STATUS_ON_ENDING =
    GBoard::component_status_t::name_t::board << 16 |
    GBoard::component_status_t::stats_t::ending;
// 控制板开始/暂停按键，低16位保留
constexpr std::uint32_t BOARD_KEY_PAUSE =
    GBoard::component_status_t::name_t::key << 16 |
    GBoard::component_status_t::stats_t::reserved;
// 上相机取图中
constexpr std::uint32_t UCAMERA_STATUS_RUN =
    GBoard::component_status_t::name_t::ucamera << 16 |
    GBoard::component_status_t::stats_t::running;
// 上相机取图结束
constexpr std::uint32_t UCAMERA_STATUS_READY =
    GBoard::component_status_t::name_t::ucamera << 16 |
    GBoard::component_status_t::stats_t::ready;
// 下相机取图中
constexpr std::uint32_t DCAMERA_STATUS_RUN =
    GBoard::component_status_t::name_t::dcamera << 16 |
    GBoard::component_status_t::stats_t::running;
// 下相机取图结束
constexpr std::uint32_t DCAMERA_STATUS_READY =
    GBoard::component_status_t::name_t::dcamera << 16 |
    GBoard::component_status_t::stats_t::ready;
// 正在清料
constexpr std::uint32_t FLOW_STATUS_CLEARING =
    GBoard::component_status_t::name_t::flow << 16 |
    GBoard::component_status_t::stats_t::running;
// 振动器正在运行: 用于强制结束逻辑的清料环节
constexpr std::uint32_t VIBRATOR_STATUS_RUNNING =
    GBoard::component_status_t::name_t::vibrator << 16 |
    GBoard::component_status_t::stats_t::running;
// 振动器停止/就绪: 用于正常结束逻辑的清料环节，下位机倒计时结束
constexpr std::uint32_t VIBRATOR_STATUS_READY =
    GBoard::component_status_t::name_t::vibrator << 16 |
    GBoard::component_status_t::stats_t::ready;
// 硬件实体按键
constexpr std::uint32_t KEY_STATUS_RUNNING =
    GBoard::component_status_t::name_t::key << 16 |
    GBoard::component_status_t::stats_t::running;
// 回收盒状态-到位
constexpr std::uint32_t RECYCLE_STATUS_RUNNING =
    GBoard::component_status_t::name_t::recycle << 16 |
    GBoard::component_status_t::stats_t::running;
// 回收盒状态-离位
constexpr std::uint32_t RECYCLE_STATUS_READY =
    GBoard::component_status_t::name_t::recycle << 16 |
    GBoard::component_status_t::stats_t::ready;



/// 光源提前点亮时间
constexpr std::uint32_t light_on_milliseconds = 1500;
/// 上光源序号
constexpr int ulight_id = 0;
/// 下光源序号
constexpr int dlight_id = 1;

namespace board {

struct frame {
  float wei;    // 电子秤数据
};

class board;

class board_observer {
 public:
  /**
   * @brief 控制板数据帧处理函数接口
   * 
   * @param uid 控制板uid
   * @param frame 控制板数据帧
   */
  virtual void handle_frame(std::string uid, frame frame) = 0;

  /**
   * @brief 
   * 
   * @param uid 控制板状态处理函数接口
   * @param status 状态值
   */
  virtual void handle_status(std::string uid, std::uint32_t status) = 0;
};

class board_subject {
 public:
  /**
   * @brief Construct a new board subject object
   * 
   * @param uid 
   */
  explicit board_subject(std::string uid) : m_uid(uid) {}

  /**
   * @brief Destroy the board subject object
   * 
   */
  virtual ~board_subject() {
    m_observers.clear();
  }

  /**
   * @brief 添加数据观察者
   * 
   * @param obs 
   */
  void attach(std::shared_ptr<board_observer> obs) {
    for (const auto &it : m_observers) if (it == obs) return;
    m_observers.push_back(obs);
  }

  /**
   * @brief 删除数据观察者
   * 
   * @param obs 
   */
  void detach(std::shared_ptr<board_observer> obs) {
    m_observers.remove(obs);
  }

  /**
   * @brief 通知所有数据观察者数据已经备好
   * 
   * @param frame 
   */
  void notify_frame(frame frame) {
    for (const auto& obs : m_observers) {
      obs->handle_frame(m_uid, frame);
    }
  }

  /**
   * @brief 通知所有状态观察者控制板状态变化
   * 
   * @param status 状态值
   */
  void notify_status(std::uint32_t status) {
    for (const auto& obs : m_observers) {
      obs->handle_status(m_uid, status);
    }
  }

 protected:
  std::string m_uid;
  std::list<std::shared_ptr<board_observer>> m_observers;
};

enum class e_task : std::uint8_t {
  null,
  unsound,
  im_calibrate,
  ai_calibrate,
};

class board : public board_subject, std::enable_shared_from_this<board> {
 public:
  explicit board(std::string uid, boost::shared_ptr<GBoard::board_plugin_api> driver);
  ~board();

  /**
   * @brief 控制板uid
   * 
   * @return std::string 
   */
  std::string uid() const { return m_handle; }

  /**
   * @brief 发送指令
   * 
   * @param str_cmd 指令字符串
   * @return int 
   */
  int send_cmd(const std::string str_cmd);

  /**
   * @brief 获取当前任务
   * 
   * @return e_task 
   */
  e_task task() const {return m_task;}

  /**
   * @brief 设置任务
   * 
   * @param t 
   * @return int 
   */
  int task(e_task t);

  /**
   * @brief 开始任务
   * 
   * @return int 
   */
  int start_task();

  /**
   * @brief 暂停任务
   * 
   * @return int 
   */
  int pasue_task();

  /**
   * @brief 停止任务
   * 
   * @return int 
   */
  int stop_task();

  /**
   * @brief 插件准备完毕，询问回收盒状态
   * 
   * @return int 
   */
  int query_recycle();

  /**
   * @brief 命令控制器推入样本
   * 
   * @return int 
   */
  int push_sample(bool is_stop);

  /**
   * @brief 点亮光源
   * 
   * @param light_id 光源序号
   * @return int 
   */
  int light_on(int light_id);

  /**
   * @brief 关闭光源
   * 
   * @param light_id 光源序号
   * @return int 
   */
  int light_off(int light_id);

  /**
   * @brief 设置步进电机方向
   * 
   * @param smotor_id 步进电机序号
   * @param direction 方向 -> 1：前进，2：后退
   * @return int 
   */
  int smotor_direction(int smotor_id, int direction);

  /**
   * @brief 获取步进电机方向
   * 
   * @param smotor_id 步进电机序号
   * @return int 方向值，小于0表示异常
   */
  int smotor_direction(int smotor_id) const {
    // std::unordered_map<int, int>::const_iterator
    auto it = m_smotor_direction.find(smotor_id);
    // 没有找到，无效id
    if (m_smotor_direction.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置步进电机前进速度
   * 
   * @param id 步进电机序号
   * @param speed 速度
   * @return int 
   */
  int smotor_positive_speed(int id, int speed);

  /**
   * @brief 获取步进电机前进速度
   * 
   * @param id 步进电机序号
   * @return int 
   */
  int smotor_positive_speed(int id) const {
    auto it = m_smotor_pos_speed.find(id);
    if (m_smotor_pos_speed.end() == it) return -1;
    return it->second;
  }

  /**
   * @brief 设置步进电机后退速度
   * 
   * @param id 步进电机序号
   * @param speed 速度
   * @return int 
   */
  int smotor_negtive_speed(int id, int speed);

  /**
   * @brief 获取步进电机后退速度
   * 
   * @param id 步进电机序号
   * @return int 
   */
  int smotor_negtive_speed(int id) const {
    auto it = m_smotor_neg_speed.find(id);
    if (m_smotor_neg_speed.end() == it) return -1;
    return it->second;
  }

  /**
   * @brief 设置步进电机位置0
   * 
   * @param id 步进电机序号
   * @param pos 位置
   * @return int 
   */
  int smotor_pre_position(int id, int pos);

  /**
   * @brief 获取步进电机位置0
   * 
   * @param id 步进电机序号
   * @return int 
   */
  int smotor_pre_position(int id) const {
    auto it = m_smotor_pre_pos.find(id);
    if (m_smotor_pre_pos.end() == it) return -1;
    return it->second;
  }

  /**
   * @brief 设置步进电机位置1
   * 
   * @param id 步进电机序号
   * @param pos 位置
   * @return int 
   */
  int smotor_start_position(int id, int pos);

  /**
   * @brief 获取步进电机位置1
   * 
   * @param id 步进电机序号
   * @return int 
   */
  int smotor_start_position(int id) const {
    auto it = m_smotor_start_pos.find(id);
    if (m_smotor_start_pos.end() == it) return -1;
    return it->second;
  }

  /**
   * @brief 设置步进电机位置2
   * 
   * @param id 步进电机序号
   * @param pos 位置
   * @return int 
   */
  int smotor_stop_position(int id, int pos);

  /**
   * @brief 获取步进电机位置2
   * 
   * @param id 步进电机序号
   * @return int 
   */
  int smotor_stop_position(int id) const {
    auto it = m_smotor_stop_pos.find(id);
    if (m_smotor_stop_pos.end() == it) return -1;
    return it->second;
  }

  /**
   * @brief 清零电子秤
   * 
   * @param id 
   * @return int 
   */
  int reset_weightor(int id);

  /**
   * @brief 校准电子秤
   * 
   * @param id 
   * @return int 
   */
  int calibrate_weightor(int id);

  /**
   * @brief 获取直流电机策略
   * 
   * @param id 电机序号
   * @return int 策略值，小于0表示异常
   */
  int dcmotor_policy(int id) const {
    auto it = m_smotor_direction.find(id);
    // 没有找到，无效id
    if (m_dcmotor_policy.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置直流电机策略
   * 对于清料直流电机 -> 1：入料时保持打开，2：入料时保持关闭
   * 
   * @param id 
   * @return int 
   */
  int dcmotor_policy(int id, int policy);

  /**
   * @brief 获取入料时的持续振动时间
   * 
   * @param id 
   * @return int 
   */
  int vibrator_input_time(int id) const {
    auto it = m_vibrator_input_time.find(id);
    if (m_vibrator_input_time.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置入料时的持续振动时间，后期改用流量相机控制
   * 
   * @param id 振动器序号
   * @param time 持续时间
   * @return int 
   */
  int vibrator_input_time(int id, int time);

  /**
   * @brief 获取清料时的持续振动时间
   * 
   * @param id 
   * @return int 
   */
  int vibrator_clear_time(int id) const {
    auto it = m_vibrator_clear_time.find(id);
    if (m_vibrator_clear_time.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置清料时的持续振动时间，后期改用流量相机控制
   * 
   * @param id 振动器序号
   * @param time 持续时间
   * @return int 
   */
  int vibrator_clear_time(int id, int time);

  /**
   * @brief 设置振动器-物料异常
   * 
   * @param id 振动器序号
   * @param value 异常码，0：没有物料
   * @return int 
   */
  int vibrator_sample_exception(int id, int value);

  /**
   * @brief 设置振动器-物料已经准备好
   * 
   * @param id 振动器序号
   * @param value 类型，0：开始时的物料准备，1：结束时的物料准备
   * @return int 
   */
  int vibrator_sample_ready(int id, int value);

  /**
   * @brief 获取振动器-中心频率
   * 
   * @param id 
   * @return int 
   */
  int vibrator_center_frequency(int id) const {
    auto it = m_vibrator_center_frequency.find(id);
    if (m_vibrator_center_frequency.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置振动器-中心频率
   * 
   * @param id 振动器序号
   * @param value 
   * @return int 
   */
  int vibrator_center_frequency(int id, int value);

/**
   * @brief 获取振动器-振动频率
   * 
   * @param id 
   * @return int 
   */
  int vibrator_vibration_frequency(int id) const {
    auto it = m_vibrator_vibration_frequnency.find(id);
    if (m_vibrator_vibration_frequnency.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置振动器-振动频率
   * 
   * @param id 振动器序号
   * @param value 
   * @return int 
   */
  int vibrator_vibration_frequency(int id, int value);


/**
   * @brief 获取振动器-出料速度
   * 
   * @param id 振动器序号
   * @return int 
   */
  int vibrator_discharge_speed(int id) const {
    auto it = m_vibrator_discharge_speed.find(id);
    if (m_vibrator_discharge_speed.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置振动器-出料速度
   * 
   * @param id 振动器序号
   * @param value 
   * @return int 
   */
  int vibrator_discharge_speed(int id, int value);

/**
   * @brief 获取振动器-电压
   * 
   * @param id 振动器序号
   * @return int 
   */
  int vibrator_voltage(int id) const {
    auto it = m_vibrator_voltage.find(id);
    if (m_vibrator_voltage.end() == it) {return -1;}
    return it->second;
  }

  /**
   * @brief 设置振动器-电压
   * 
   * @param id 振动器序号
   * @param value 
   * @return int 
   */
  int vibrator_voltage(int id, int value);


  /**
   * @brief 相机图像抓取
   * 
   * @param id 相机序号
   * @param value 1：开始抓取，2：抓取完成
   * @return int 
   */
  int camera_frame_acquire(int id, int value);


  /**
   * @brief  发送流量相机状态
   * 
   * @param value 10：空， 11：开始， 12：循环， 13：停止
   * @return int 
   */
  int fc_status(int value);

  /**
   * @brief 获取控制板最大触发次数
   * 
   * @return int 
   */
  int max_trigger_count() const {
    return m_max_trigger_count;
  }

  /**
   * @brief 设置控制板最大触发次数
   * 
   * @param count 
   * @return int 
   */
  int max_trigger_count(int count);

  /**
   * @brief 设置拍照延时
   * 
   * @param time 
   * @return int 
   */
  int capture_delay(int time);

 private:
  boost::shared_ptr<GBoard::board_plugin_api> m_driver;
  // 控制板handle
  std::string m_handle;
  // 控制板任务
  e_task m_task;
  // 步进电机序号:步进电机方向（1：前进，2：后退）
  std::unordered_map<int, int> m_smotor_direction;
  // 步进电机序号:步进电机前进速度
  std::unordered_map<int, int> m_smotor_pos_speed;
  // 步进电机序号:步进电机后退速度
  std::unordered_map<int, int> m_smotor_neg_speed;
  // 步进电机序号:步进电机触发位置0(预震时电机位置)
  std::unordered_map<int, int> m_smotor_pre_pos;
  // 步进电机序号:步进电机触发位置1(开始震动时电机位置)
  std::unordered_map<int, int> m_smotor_start_pos;
  // 步进电机序号:步进电机触发位置2(停止震动时电机位置)
  std::unordered_map<int, int> m_smotor_stop_pos;
  // 直流电机序号:直流电机策略
  std::unordered_map<int, int> m_dcmotor_policy;
  // 振动器序号:入料持续振动时间
  std::unordered_map<int, int> m_vibrator_input_time;
  // 振动器序号:清料持续振动时间
  std::unordered_map<int, int> m_vibrator_clear_time;
  // 振动器序号:物料异常-没有物料
  std::unordered_map<int, int> m_vibrator_exception_empty;
  // 振动器序号:物料已准备好-类型（开始/结束）
  std::unordered_map<int, int> m_vibrator_ready_type;
  // 振动器序号:中心频率
  std::unordered_map<int, int> m_vibrator_center_frequency;
  // 振动器序号:振动频率
  std::unordered_map<int, int> m_vibrator_vibration_frequnency;
  // 振动器序号:出料速度
  std::unordered_map<int, int> m_vibrator_discharge_speed;
  // 振动器序号:电压
  std::unordered_map<int, int> m_vibrator_voltage;
  // 拍照延时
  int m_capture_delay;
  // 最大触发次数
  int m_max_trigger_count;
};

}  // namespace board

#endif  // MODULE_BOARD_BOARD_H_
