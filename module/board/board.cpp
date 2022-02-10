/**
 * @file board.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-08
 * @date 2021-10-21 修改震动器，相机接口 0.0.2
 * @copyright Copyright (c) 2021
 * 
 */

#include "module/board/board.h"
#include "board_plugin_api.hpp"
#include <cstdint>
namespace board {

board::board(std::string uid, boost::shared_ptr<GBoard::board_plugin_api> driver)
    : board_subject(uid), m_driver(driver), m_handle(uid), m_task(e_task::unsound) {}

board::~board() {
  m_driver->disconnect_board(m_uid);
}

int board::send_cmd(const std::string str_cmd) {
  auto ec = m_driver->send_cmd(m_handle, str_cmd);
  if (ec != GBoard::board_error_t::success) {
    return static_cast<int>(ec);
  }
  return 0;
}

/**
 * @brief 设置任务
 * 
 * @param t 
 * @return int 
 */
int board::task(e_task t) {
  auto ec = m_driver->set_task(m_uid, static_cast<GBoard::board_tasks_t>(t));
  if (ec != GBoard::board_error_t::success) {
    return static_cast<int>(ec);
  }
  m_task = t;
  return 0;
}

/**
 * @brief 开始任务
 * 
 * @return int 
 */
int board::start_task() {
  return static_cast<int>(m_driver->start_task(m_uid));
}

/**
 * @brief 暂停任务
 * 
 * @return int 
 */
int board::pasue_task() {
  return static_cast<int>(m_driver->pause_task(m_uid));
}

/**
 * @brief 停止任务
 * 
 * @return int 
 */
int board::stop_task() {
  return static_cast<int>(m_driver->stop_task(m_uid));
}

/**
 * @brief 插件准备完毕，询问回收盒状态
 * 
 * @return int 
 */
int board::query_recycle() {
  return static_cast<int>(m_driver->query_recycle(m_uid));
}

// /**
//  * @brief 命令控制器推入样本
//  *
//  * @return int
//  */
// int board::push_sample(bool is_stop) {
//   if (!is_stop) return send_cmd("BB50000000000D0A");
//   return send_cmd("BB50000000010D0A");
// }

/**
 * @brief 点亮光源
 * 
 * @param light_id 光源序号
 * @return int 
 */
int board::light_on(int light_id) {
  return static_cast<int>(m_driver->set_light_info(m_uid,
      {static_cast<std::uint8_t>(light_id), GBoard::light_info::on, 0xffff}));
}

/**
 * @brief 关闭光源
 * 
 * @param light_id 光源序号
 * @return int 
 */
int board::light_off(int light_id) {
  return static_cast<int>(m_driver->set_light_info(m_uid,
      {static_cast<std::uint8_t>(light_id), GBoard::light_info::off, 0xffff}));
}

/**
 * @brief 设置步进电机方向
 * 
 * @param smotor_id 步进电机序号
 * @param direction 方向 -> 1：前进，2：后退
 * @return int 
 */
int board::smotor_direction(int smotor_id, int direction) {
  if (direction != 1 && direction != 2) return 4;
  auto ret = m_driver->set_smotor_info(m_uid, {
      static_cast<std::uint8_t>(smotor_id),
      GBoard::smotor_info::direction,
      static_cast<std::uint16_t>(direction)});
  if (GBoard::board_error_t::success == ret) {
    m_smotor_direction[smotor_id] = direction;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置步进电机前进速度
 * 
 * @param id 步进电机序号
 * @param speed 速度
 * @return int 
 */
int board::smotor_positive_speed(int id, int speed) {
  auto ret = m_driver->set_smotor_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::smotor_info::positive_speed,
      static_cast<std::uint16_t>(speed)});
  if (GBoard::board_error_t::success == ret) {
    m_smotor_pos_speed[id] = speed;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置步进电机后退速度
 * 
 * @param id 步进电机序号
 * @param speed 速度
 * @return int 
 */
int board::smotor_negtive_speed(int id, int speed) {
  auto ret = m_driver->set_smotor_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::smotor_info::negative_speed,
      static_cast<std::uint16_t>(speed)});
  if (GBoard::board_error_t::success == ret) {
    m_smotor_neg_speed[id] = speed;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置步进电机位置0
 * 
 * @param id 步进电机序号
 * @param pos 位置
 * @return int 
 */
int board::smotor_pre_position(int id, int pos) {
  auto ret = m_driver->set_smotor_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::smotor_info::position_0,
      static_cast<std::uint16_t>(pos)});
  if (GBoard::board_error_t::success == ret) {
    m_smotor_pre_pos[id] = pos;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置步进电机位置1
 * 
 * @param id 步进电机序号
 * @param pos 位置
 * @return int 
 */
int board::smotor_start_position(int id, int pos) {
  auto ret = m_driver->set_smotor_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::smotor_info::position_1,
      static_cast<std::uint16_t>(pos)});
  if (GBoard::board_error_t::success == ret) {
    m_smotor_start_pos[id] = pos;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置步进电机位置2
 * 
 * @param id 步进电机序号
 * @param pos 位置
 * @return int 
 */
int board::smotor_stop_position(int id, int pos) {
  auto ret = m_driver->set_smotor_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::smotor_info::position_2,
      static_cast<std::uint16_t>(pos)});
  if (GBoard::board_error_t::success == ret) {
    m_smotor_stop_pos[id] = pos;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 清零电子秤
 * 
 * @param id 
 * @return int 
 */
int board::reset_weightor(int id) {
  return static_cast<int>(m_driver->set_weightor_info(m_uid,
      {static_cast<std::uint8_t>(id), GBoard::weightor_info::clear, 0xffff}));
}

/**
 * @brief 校准电子秤
 * 
 * @param id 
 * @return int 
 */
int board::calibrate_weightor(int id) {
  return static_cast<int>(m_driver->set_weightor_info(m_uid,
      {static_cast<std::uint8_t>(id), GBoard::weightor_info::calibrate, 0xffff}));
}

/**
 * @brief 设置直流电机策略
 * 对于清料直流电机 -> 1：入料时保持打开，2：入料时保持关闭
 * 
 * @param id 
 * @return int 
 */
int board::dcmotor_policy(int id, int policy) {
  GBoard::dcmotor_info info;
  if (policy == 1) {
    info.value = GBoard::dcmotor_info::open_on_vibrate;
  } else if (policy == 2) {
    info.value = GBoard::dcmotor_info::close_on_vibrate;
  } else {
    return 4;
  }
  info.id = static_cast<std::uint8_t>(id);
  auto ret = m_driver->set_dcmotor_info(m_uid, info);
  if (GBoard::board_error_t::success == ret) {
    m_dcmotor_policy[id] = policy;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置入料时的持续振动时间，后期改用流量相机控制
 * 
 * @param id 振动器序号
 * @param time 持续时间
 * @return int 
 */
int board::vibrator_input_time(int id, int time) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::input_vibrate,
      static_cast<std::uint16_t>(time)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_input_time[id] = time;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置清料时的持续振动时间，后期改用流量相机控制
 * 
 * @param id 振动器序号
 * @param time 持续时间
 * @return int 
 */
int board::vibrator_clear_time(int id, int time) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::clear_vibrate,
      static_cast<std::uint16_t>(time)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_clear_time[id] = time;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 振动器中的物料异常
 * 
 * @param id 振动器序号
 * @param value 异常码，0：没有物料
 * @return int 
 */
int board::vibrator_sample_exception(int id, int value) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::exception_vibrate,
      static_cast<std::uint16_t>(value)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_exception_empty[id] = value;
  }
  return static_cast<int>(ret);
  // return send_cmd("BB13000200000D0A");
}

/**
 * @brief 振动器中的物料已经准备好
 * 
 * @param id 振动器序号
 * @param value 类型，0：开始时的物料准备，1：结束时的物料准备
 * @return int 
 */
int board::vibrator_sample_ready(int id, int value) {
  if (value != 0 && value != 1) return 4;
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::ready_vibrate,
      static_cast<std::uint16_t>(value)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_ready_type[id] = value;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置-振动器-中心频率
 * 
 * @param id 振动器序号
 * @param value 
 * @return int 
 */
int board::vibrator_center_frequency(int id, int value) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::center_frequency,
      static_cast<std::uint16_t>(value)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_center_frequency[id] = value;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置-振动器-振动频率
 * 
 * @param id 振动器序号
 * @param value 
 * @return int 
 */
int board::vibrator_vibration_frequency(int id, int value) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::vibration_frequency,
      static_cast<std::uint16_t>(value)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_vibration_frequnency[id] = value;
  }
  return static_cast<int>(ret);
}


/**
 * @brief 设置-振动器-出料速度
 * 
 * @param id 振动器序号
 * @param value 
 * @return int 
 */
int board::vibrator_discharge_speed(int id, int value) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::discharge_speed,
      static_cast<std::uint16_t>(value)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_discharge_speed[id] = value;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置-振动器-电压
 * 
 * @param id 振动器序号
 * @param value 
 * @return int 
 */
int board::vibrator_voltage(int id, int value) {
  auto ret = m_driver->set_vibrator_info(m_uid, {
      static_cast<std::uint8_t>(id),
      GBoard::vibrator_info::voltage,
      static_cast<std::uint16_t>(value)});
  if (GBoard::board_error_t::success == ret) {
    m_vibrator_voltage[id] = value;
  }
  return static_cast<int>(ret);
}



/**
 * @brief 相机图像抓取
 * 
 * @param id 相机序号
 * @param key 1：开始抓取，2：抓取完成
 * @return int 
 */
int board::camera_frame_acquire(int id, int key) {
  GBoard::board_error_t ret = GBoard::board_error_t::success;
  switch (key) {
  case 1:
    ret = m_driver->set_camera_info(m_uid, {
    static_cast<std::uint8_t>(id),
    GBoard::camera_info::start_pic});
    break;
  case 2:
    ret = m_driver->set_camera_info(m_uid, {
    static_cast<std::uint8_t>(id),
    GBoard::camera_info::end_pic});
    break;
  default:
    return 4;
  }
  return static_cast<int>(ret);
  // if (0 == id && 1 == value) return send_cmd("BB140001FFFF0D0A");
  // if (0 == id && 2 == value) return send_cmd("BB140002FFFF0D0A");
  // if (1 == id && 1 == value) return send_cmd("BB140101FFFF0D0A");
  // if (1 == id && 2 == value) return send_cmd("BB140102FFFF0D0A");
}

/**
 * @brief  发送流量相机状态
 * 
 * @param value 10：空， 11：开始， 12：循环， 13：停止
 * @return int 
 */
int board::fc_status(int key) {
  GBoard::board_error_t ret = GBoard::board_error_t::success;
  switch (key) {
  case 10:
    ret = m_driver->set_camera_info(m_uid, {
    static_cast<std::uint8_t>(2),
    GBoard::camera_info::status_empty});
    break;
  case 11:
    ret = m_driver->set_camera_info(m_uid, {
    static_cast<std::uint8_t>(2),
    GBoard::camera_info::status_start});
    break;
  case 12:
    ret = m_driver->set_camera_info(m_uid, {
    static_cast<std::uint8_t>(2),
    GBoard::camera_info::status_loop});
    break;
  case 13:
    ret = m_driver->set_camera_info(m_uid, {
    static_cast<std::uint8_t>(2),
    GBoard::camera_info::status_stop});
    break;
  default:
    return 4;
  }
  return static_cast<int>(ret);
}



/**
 * @brief 设置控制板最大触发次数
 * 
 * @param count 
 * @return int 
 */
int board::max_trigger_count(int count) {
  auto ret = m_driver->set_trigger_info(m_uid,
    {GBoard::trigger_info::max_trigger, static_cast<std::uint16_t>(count)});

  if (GBoard::board_error_t::success == ret) {
    m_max_trigger_count = count;
  }
  return static_cast<int>(ret);
}

/**
 * @brief 设置拍照延时
 * 
 * @param time 
 * @return int 
 */
int board::capture_delay(int time) {
  auto ret = m_driver->set_trigger_info(m_uid,
    {GBoard::trigger_info::capture_delay, static_cast<std::uint16_t>(time)});

  if (GBoard::board_error_t::success == ret) {
    m_capture_delay = time;
  }
  return static_cast<int>(ret);
}

}  // namespace board
