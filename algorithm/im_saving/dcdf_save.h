/**
 * @file dcdf_save.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ALGORITHM_IM_SAVING_DCDF_SAVE_H_
#define ALGORITHM_IM_SAVING_DCDF_SAVE_H_

#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>

#include "generator/dcdf_generator.h"
#include "calibrate/calibrate.h"

namespace algorithm {

enum class tengine : std::uint8_t {
  dcdf,
  calibrator,
};

struct batch_frame {
  std::shared_ptr<camera::frame> ua;
  std::shared_ptr<camera::frame> db;
  std::shared_ptr<camera::frame> da;
  std::shared_ptr<camera::frame> ub;
  float wei;
  std::uint32_t id;
  std::string time_str;
  std::string grain_type;
  std::string abnormal_type;
};

class dcdf_obs;
class cali_obs;
class dcdf_save {
 public:
  explicit dcdf_save(std::shared_ptr<generator::dcdf_engine> dcdf_engine,
      std::shared_ptr<calibrate::calibrator> cali_engine,
      std::string sv_path, std::string device_id);
  ~dcdf_save();

  /**
   * @brief Set the path object
   * 
   * @param path 需要有文件夹结束符
   * @return int 
   */
  int set_path(std::string path);
  int enable();
  int disable();

 private:
  void save_entity(batch_frame f, tengine engine);

 private:
  bool m_save_enable;
  std::shared_ptr<generator::dcdf_engine> m_dcdf_engine;
  std::shared_ptr<calibrate::calibrator> m_cali_engine;
  boost::asio::thread_pool m_tpool;
  std::string m_path;
  std::string m_dev_id;
  std::shared_ptr<dcdf_obs> m_dcdf_obs;
  std::shared_ptr<cali_obs> m_cali_obs;
  std::atomic<std::uint32_t> m_remain;
};

}  // namespace algorithm

#endif  // ALGORITHM_IM_SAVING_DCDF_SAVE_H_
