/**
 * @file board_plugin_api.hpp
 * @author Junjun Dong(dongjunjun@gaozhe.com.cn)
 * @copyright Copyright (c) 2021
 * @brief 嵌入式控制板插件接口设计，其控制的外围器件包含：相机，光源，电机，震动器等
 * @version 2.0.0
 * @date 2021-04-22
 * @date 2021-07-26
 * @date 2021-08-24 更新光源配置选项（+ on/off），更新整机状态（+ grab_ready）
 * @date 2021-09-28 callback函数支持user数据
 * @date 2021-09-28 更新协议：增加样本数据抓取相关指令，增加入料指令
 * @date 2021-10-09 更改handle类型(使用串口设备名) void -> std::string
 * @date 2021-10-18 添加回收盒recycle状态处理 2.0.1
 * @date 2021-10-18 添加端口匹配 ttyUSB? ttyTHS? 2.0.2
 * @date 2021-10-19 添加无效指令标红 2.0.3
 * @date 2021-10-20 添加震动器，相机的写指令 2.0.4
 * @date 2021-10-22 修改校准的开始结束指令 2.0.5
 * @date 2021-10-27 添加状态-整机-正在停止指令 2.0.6
 * @date 2021-10-29 添加状态-实体硬件按键信息key 2.0.7
 * @date 2021-11-01 添加相机延时、振动器中心频率、振动频率、出料速度、电压 2.0.8
 * @date 2021-11-03 添加串口脏数据清理 2.0.9
 * @date 2021-11-04 (djj) 更新状态指令：添加相机组件
 * @date 2021-11-05 修改串口脏数据清理 2.0.10
 * @date 2021-11-05 (djj) 更新指令匹配方案 2.1.0
 * @date 2021-11-26 添加普通用户结束逻辑 2.1.2
 * @date 2021-12-07 添加心跳信号 2.1.3
 * @date 2021-12-14 状态指令+电子称数据指令 回复 2.1.4
 * @date 2021-12-15 流量相机灯源开关控制 2.1.5
 * @date 2021-12-22 log改为boost 2.2.0
 * @date 2022-01-17 修改回收盒状态
 * 
 */

#ifndef BOARD_PLUGIN_API_HPP_
#define BOARD_PLUGIN_API_HPP_

#include <cstdint>
#include <cmath>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <functional>
#include <utility>
#include <iomanip>
#include <unordered_map>

#include <boost/config.hpp>  // for BOOST_SYMBOL_VISIBLE
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#define BOARD_CREATOR_SYMBOL "create_board_plugin"

namespace GBoard {

/**
 * @brief 控制板操作错误码定义
 * 
 */
enum class board_error_t : std::uint8_t {
  success = 0,  // 正常
  error,        // 操作失败
  handle,       // 句柄错误
  memory,       // 内存错误
  argument,     // 参数错误
  not_config,   // 未配置
  invalid_id,   // 无效ID
  invalid_cmd,  // 无效命令
  timeout,      // 超时
};
   
// 协议中实际为4个比特位
enum class instruction_t : std::uint8_t {
  unknown = 0x0,
  write = 0x1,
  read = 0x2,
  status = 0x3,
  data = 0x4,
  handshake = 0x8,
  start = 0xa,
  pause = 0xb,
  stop = 0xc,
  heartbeat = 0xf,
};

/**
 * @brief 控制板状态，主要分为以下几大类，初始状态（ready），暂停状态（pause），
 *  工作状态（由各个工作器件组成）和异常状态（由各个器件的异常组成）
 * 
 */
struct component_status_t {
  enum name_t : std::uint16_t {
    unknown = 0x0000,         // 未知
    step_motor0 = 0x0100,     // 步进电机0（仓门）
    step_motor1 = 0x0101,     // 步进电机1（入料）
    dc_motor = 0x0200,        // 直流电机（清料）
    ulight = 0x0300,          // 光源0（上）
    dlight = 0x0301,          // 光源1（下）
    flight = 0x0302,          // 光源2（流量相机）
    vibrator = 0x0400,        // 震动器
    weightor = 0x0500,        // 电子秤
    recycle = 0x0600,         // 回收盒
    key = 0x0700,             // 硬件实体按键
    ucamera = 0x0800,         // 相机（上）
    dcamera = 0x0801,         // 相机（下）
    flow    = 0x0802,         // 流量相机
    board = 0xff00,           // 控制板（整机）
  } name;

  enum stats_t : std::uint16_t {
    reserved = 0x0000,        // 保留
    invalid = 0x0001,         // 无效指令
    ready = 0x0002,           // 就绪（停止）
    running = 0x0003,         // 运行中
    pause = 0x0004,           // 暂停
    exception = 0x0005,       // 异常
    grab_ready = 0x0006,      // 载物板到位，已准备好进行样本数据抓取
    // grab_start = 0x0007,      // 样本数据抓取开始
    ending = 0x0007,          // 正在停止
    // grad_done = 0x0008,       // 样本数据抓取完成
    query = 0xf000,           // 查询
  } status;
};

/**
 * @brief 控制板任务类型
 * 
 */
enum class board_tasks_t : std::uint8_t {
  null = 0,       // 无任务
  unsound,        // 不完善粒任务
  im_calibrate,   // 校准任务（图像）
  ai_calibrate,   // 校准任务（算法）
};

/**
 * @brief 控制板的软硬件版本信息,可用作控制板的UUID
 * 
 */
struct version_info {
  // 硬件版本号
  // unsigned char hardware_version[16];
  std::string hardware_version;
  // 软件版本号
  // unsigned char software_version[16];
  std::string software_version;
};

struct weightor_info {
  std::uint8_t id;      // 序号
  enum func : std::uint8_t {
    clear = 0x03,       // 清零
    read = 0x04,        // 读取数据
    calibrate = 0x05,   // 校准
    shift = 0x06,       // 偏移值(小麦颗粒数)
  } key;
  std::uint16_t value;
};

/**
 * @brief 光源信息，目前情况，按位置有上下光源，再按对样品打光的位置分为明暗光源
 *  光源的需求由相机决定
 */
struct light_info {
  std::uint8_t id;       // 光源序号
  enum : std::uint8_t {
    on_time = 0x01,     // 光源点亮时间
    on = 0x02,          // 打开光源
    off = 0x03,         // 关闭光源
  } key;
  std::uint16_t value;  // 光源点亮时间
};

/**
 * @brief 直流电机信息
 * 
 */
struct dcmotor_info {
  std::uint8_t id;              // 直流电机序号
  enum : std::uint16_t {
    open_on_vibrate = 0x0001,   // 针对仓门电机，震动器入料时保持打开
    close_on_vibrate = 0x0002,  // 针对仓门电机，震动器入料时保持关闭
  } value;
};

/**
 * @brief 相机信息
 * 
 */
struct camera_info {
  std::uint8_t id;              // 相机序号
  enum : std::uint8_t {
    start_pic = 0x01,   // 开始取图
    end_pic = 0x02,  // 结束取图
    status_empty = 0x10,  // 流量相机-状态空
    status_start = 0x11,  // 流量相机-状态开始
    status_loop = 0x12,  // 流量相机-状态循环
    status_stop = 0x13,  // 流量相机-状态停止
  } key;
};

/**
 * @brief 步进电机信息，目前控制板系统中，所有可被设置的触发，均可以由电机位置决定
 *  如，震动器的启停
 */
struct smotor_info {
  enum direction : std::uint16_t {
    positive = 1,
    negative = 2,
  };

  std::uint8_t id;          //< 步进电机序号
  enum : std::uint8_t {
    stroke = 0x01,          //< 电机行程
    step = 0x02,            //< 电机步程
    direction = 0x03,       //< 电机方向，1：正向，2：反向
    positive_speed = 0x04,  //< 前进速度
    negative_speed = 0x05,  //< 后退速度
    position_0 = 0x06,      //< 预震时电机位置
    position_1 = 0x07,      //< 开始震动时电机位置
    position_2 = 0x08,      //< 停止震动时电机位置
    start = 0x09,           //< 开始电机
    stop = 0x0A,            //< 停止电机
    count = 0xFF,           //< 电机个数
  } key;
  std::uint16_t value;      //< 实际数值
};

/**
 * @brief 震动器信息，震动器的启停由内部业务逻辑决定
 * 
 */
struct vibrator_info {
  std::uint8_t id;                 // 震动器序号
  // 震动策略（震动持续时间）：目前系统中有，开始时的预震时间和清料时的持续震动时间
  enum : std::uint8_t {
    input_vibrate = 0x00,        // 开始进料时震动
    clear_vibrate = 0x01,        // 最后清料时震动
    exception_vibrate = 0x02,    // 物料异常
    ready_vibrate = 0x03,        // 物料已准备好
    center_frequency = 0x04,     // 中心频率
    vibration_frequency = 0x05,  // 振动频率
    discharge_speed = 0x06,      // 出料速度
    voltage = 0x07,              // 电压
  } key;
  std::uint16_t value;
};

/**
 * @brief 控制板触发器信息，目前是给相机触发信号
 * 
 */
struct trigger_info {
  enum : std::uint8_t {
    //< 一次触发信号数量（1个相机：2个信号）
    signal_count = 0x00,
    // 内部信号间隔时间
    //< 针对相机，给其触发信号的间隔时间（受相机的帧率限制）
    // 如果给的隔间时间太短，则会导致相机丢帧
    internal_period = 0x10,
    // 外部信号间隔时间
    //< 针对两台不同相机，给其触发信号的间隔时间
    external_period = 0x11,
    //< 触发间隔时间（针对图像校准）
    trigger_period = 0x20,
    //< 拍照延时（等载物板上的颗粒稳定）
    capture_delay = 0x30,
    //< 最大触发次数
    max_trigger = 0xFF,
  } key;
  std::uint16_t value;      //< key对应的数值
};

/**
 * @brief 嵌入式控制板数据帧输出
 * 
 */
struct board_frame {
  enum frame_t : std::uint8_t {
    unknown = 0x40,         // 未知
    weightor = 0x41,        // 电子秤
    weightor_keep = 0x42,   // 电子秤保存值
    camera0 = 0x43,         // 0号相机（上）
    camera1 = 0x44,         // 1号相机（下）
  } name;                   // 参考协议, 高四位为数据指令标志(0X4), 低四位是类型
  std::uint32_t value;      // 参考协议, 实际有效位为32bit
};

/**
 * @brief 嵌入式控制板插件API定义
 * 
 */
class BOOST_SYMBOL_VISIBLE board_plugin_api {
 public:
  /**
   * @brief 获取插件名
   * 
   * @return std::string 插件名
   */
  virtual std::string name() const = 0;

  /**
   * @brief 枚举所有控制板
   * 
   * @param board_list 获取到的控制板列表
   * @return board_error_t
   */
  virtual board_error_t
  enum_board(std::shared_ptr<std::vector<std::string>> board_list) = 0;

  /**
   * @brief 连接（打开）控制板
   * 
   * @param phandle 控制板
   * @return board_error_t 
   */
  virtual board_error_t connect_board(std::string uid) = 0;

  /**
   * @brief 断开连接控制板
   * 
   * @param phandle 句柄
   * @return board_error_t 
   */
  virtual board_error_t disconnect_board(std::string uid) = 0;

  /**
   * @brief 获取控制板基本信息
   * 
   * @param phandle 句柄
   * @param pinfo 
   * @return board_error_t 
   */
  virtual board_error_t get_version_info(std::string uid, version_info* info) = 0;

  using status_cb = std::function<
    void(std::string uid, component_status_t status, void* puser)>;
  /**
   * @brief 设置控制板状态改变回调函数
   * 
   * @param phandle 句柄
   * @param cb_status 状态回调函数
   * @param puser 用户数据
   * @return board_error_t 
   */
  virtual board_error_t set_status_callback(status_cb cb, void* puser) {
    m_status_cb = cb;
    m_pstatus_user = puser;
    return board_error_t::success;
  }

  using frame_cb = std::function<
    void(std::string uid, board_frame frame, void* puser)>;
  /**
   * @brief 设置控制板数据帧回调函数
   * 
   * @param phandle 句柄
   * @param cb_im 控制板数据帧回调函数
   * @param puser 用户数据
   * @return board_error_t 
   */
  virtual board_error_t set_data_callback(frame_cb cb, void* puser) {
    m_frame_cb = cb;
    m_pframe_user = puser;
    return board_error_t::success;
  }

  /**
   * @brief 设置当前控制板任务，成功完成设置后，控制板状态应转为ready
   * 
   * @param phandle 句柄
   * @param tasks 任务类型
   * @return board_error_t 
   */
  virtual board_error_t set_task(std::string uid, board_tasks_t task) = 0;

  /**
   * @brief 获取当前控制板任务
   * 
   * @param phandle 句柄
   * @param tasks 任务类型
   * @return board_error_t 
   */
  virtual board_error_t get_task(std::string uid, board_tasks_t* task) = 0;

  /**
   * @brief 开始当前任务，控制板由ready或pause状态转变为工作或异常状态
   * 
   * @param phandle 句柄
   * @return board_error_t 
   */
  virtual board_error_t start_task(std::string uid) = 0;

  /**
   * @brief 暂停当前任务，控制板由工作状态转为pause或异常状态
   * 
   * @param phandle 句柄
   * @return board_error_t 
   */
  virtual board_error_t pause_task(std::string uid) = 0;

  /**
   * @brief 停止任务，控制板由工作或pasue状态转为ready或异常状态
   * 
   * @param phandle 句柄
   * @return board_error_t 
   */
  virtual board_error_t stop_task(std::string uid) = 0;

  /**
   * @brief Get the weightor info object
   * 
   * @param phandle 
   * @param w 
   * @return board_error_t 
   */
  virtual board_error_t
  get_weightor_info(std::string uid, weightor_info* w) = 0;

  /**
   * @brief Set the weightor info object
   * 
   * @param phandle 
   * @param w 
   * @return board_error_t 
   */
  virtual board_error_t
  set_weightor_info(std::string uid, weightor_info w) = 0;

  /**
   * @brief 获取光源信息
   * 
   * @param phandle 
   * @param l 
   * @return board_error_t 
   */
  virtual board_error_t
  get_light_info(std::string uid, light_info* l) = 0;

  /**
   * @brief Set the light info object
   * 
   * @param phandle 
   * @param l 
   * @return board_error_t 
   */
  virtual board_error_t
  set_light_info(std::string uid, light_info l) = 0;

  /**
   * @brief Get the vibrator info object
   * 
   * @param phandle 
   * @param v 
   * @return board_error_t 
   */
  virtual board_error_t
  get_vibrator_info(std::string uid, vibrator_info* v) = 0;

  /**
   * @brief Set the vibrator info object
   * 
   * @param phandle 
   * @param v 
   * @return board_error_t 
   */
  virtual board_error_t
  set_vibrator_info(std::string uid, vibrator_info v) = 0;

  /**
   * @brief Get the dcmotor info object
   * 
   * @param phandle 
   * @param m 
   * @return board_error_t 
   */
  virtual board_error_t
  get_dcmotor_info(std::string uid, dcmotor_info* m) = 0;

  /**
   * @brief Set the dcmotor info object
   * 
   * @param phandle 
   * @param m 
   * @return board_error_t 
   */
  virtual board_error_t
  set_dcmotor_info(std::string uid, dcmotor_info m) = 0;

  /**
   * @brief Get the camera info object
   * 
   * @param phandle 
   * @param m 
   * @return board_error_t 
   */
  virtual board_error_t
  get_camera_info(std::string uid, camera_info* m) = 0;

  /**
   * @brief Set the camera info object
   * 
   * @param phandle 
   * @param m 
   * @return board_error_t 
   */
  virtual board_error_t
  set_camera_info(std::string uid, camera_info m) = 0;

  /**
   * @brief Get the motor info object
   * 
   * @param phandle 
   * @param m 
   * @return board_error_t 
   */
  virtual board_error_t
  get_smotor_info(std::string uid, smotor_info* m) = 0;

  /**
   * @brief Set the motor info object
   * 
   * @param phandle 
   * @param m 
   * @return board_error_t 
   */
  virtual board_error_t
  set_smotor_info(std::string uid, smotor_info m) = 0;

  /**
   * @brief Get the trigger info object
   * 
   * @param phandle 
   * @param t 
   * @return board_error_t 
   */
  virtual board_error_t
  get_trigger_info(std::string uid, trigger_info* t) = 0;

  /**
   * @brief Set the trigger info object
   * 
   * @param phandle 
   * @param t 
   * @return board_error_t 
   */
  virtual board_error_t
  set_trigger_info(std::string uid, trigger_info t) = 0;

  /**
   * @brief 发送指令
   * 
   * @param phandle 板子句柄
   * @param str_cmd 指令字符串
   * @return board_error_t 
   */
  virtual board_error_t send_cmd(std::string uid, std::string str_cmd) = 0;

  /**
   * @brief 插件已添加完毕，主动询问回收盒状态
   * 
   * @param phandle 板子句柄
   * @param str_cmd 指令字符串
   * @return board_error_t 
   */
  virtual board_error_t query_recycle(std::string uid) = 0;


  /**
   * @brief 通过creator symbol寻找插件
   * 
   * @tparam T 
   * @param plugins 插件路径
   * @param symbol 插件的creator symbol
   * @return std::vector<boost::shared_ptr<T>> 插件列表
   */
  template<typename T>
  static std::vector<boost::shared_ptr<T>> find_plugins(
      const std::vector<boost::dll::fs::path>& plugins,
      std::string symbol) {
    std::vector<boost::shared_ptr<T>> found_plugins;
    for (std::size_t i = 0; i < plugins.size(); ++i) {
      boost::dll::shared_library lib(
          plugins[i], boost::dll::load_mode::append_decorations);
      if (!lib.has(symbol.c_str())) {
          continue;
      }

      typedef boost::shared_ptr<T>(create_t)();
      boost::function<create_t> creator =
          boost::dll::import_alias<create_t>(
              boost::move(lib), symbol.c_str());
      found_plugins.push_back(creator());
    }
    return found_plugins;
  }

 protected:
  std::string int2hex(std::uint32_t id, int w) {
    std::uint32_t max = std::pow(2, w * 4) - 1;
    if (id > max) return "";
    std::stringstream hex_str;
    hex_str << std::uppercase
            << std::setfill('0')
            << std::setw(w)
            << std::hex
            << id;
    return hex_str.str();
  }

  int hex2value(const char c) {
    int ret = 0;
    if (c >= '0' && c <= '9') {
      ret = static_cast<int>(c - '0');
    } else if (c >= 'a' && c <= 'z') {
      ret = static_cast<int>(c - 'a') + 10;
    } else if (c >= 'A' && c <= 'Z') {
      ret = static_cast<int>(c - 'A') + 10;
    } else {
      ret = -1;
    }
    return ret;
  }

  int hex2int(std::string hex, int w) {
    if (hex.size() < w) return -1;
    int ret = 0;
    const char* phex = hex.c_str();
    for (int i = w - 1; i >= 0; --i) {
      int cur = hex2value(*phex);
      if (cur < 0) return -1;
      cur &= 0xf;
      ret += cur << (i * 4);
      phex++;
    }
    return ret;
  }

 protected:
  // 状态回调函数
  status_cb m_status_cb;
  void* m_pstatus_user;
  // 数据回调函数
  frame_cb m_frame_cb;
  void* m_pframe_user;
};

}  // namespace GBoard

#endif  // BOARD_PLUGIN_API_HPP_
