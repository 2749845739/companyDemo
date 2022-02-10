/**
 * @file subject.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODULE_CAMERA_COMMON_H_
#define MODULE_CAMERA_COMMON_H_

#include <cstdint>
#include <memory>
#include <string>

namespace camera {

struct frame {
  std::string uid;                        // 相机uid
  std::uint32_t w;                        // 图像宽度
  std::uint32_t h;                        // 图像高度
  std::shared_ptr<std::uint8_t> data;     // 图像数据指针
};

enum class t_trig_mode : std::uint8_t {
  not_trig,   // 主动get frame
  hardware,   // 硬件触发
  software,   // 软件触发
};

class camera_observer {
 public:
  // virtual void handle_state(state state) = 0;
  virtual void handle_frame(frame frame) = 0;
};

enum class state : std::uint16_t {
  lost,
  connected,
};
class camera_status_observer {
 public:
  virtual void handle_state(state state) = 0;
};

}  // namespace camera

#endif  // MODULE_CAMERA_COMMON_H_
