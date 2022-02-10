/**
 * @file dcdf.h
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef ALGORITHM_GRAINEVAL_DCDF_H_
#define ALGORITHM_GRAINEVAL_DCDF_H_

#include <memory>
#include <string>
#include <thread>
#include <queue>
#include <list>

#include <boost/core/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "algorithm/graineval/graineval_api.hpp"

#include "generator/dcdf_generator.h"

namespace algorithm {

class ge_obs_sample_result {
 public:
  virtual void sample_result(algorithm::result res) = 0;
};

class ge_obs_batch_result {
 public:
  virtual void batch_result(algorithm::result res) = 0;
};

class dcdf_fobs;
class dcdf_sobs;
class dcdf : private boost::noncopyable {
 public:
 /**
  * @brief Construct a new dcdf object
  * 
  * @param dcdf_engine 
  * @param dev_id 
  */
  explicit dcdf(
      std::shared_ptr<generator::dcdf_engine> dcdf_engine,
      std::string dev_id);

  /**
   * @brief Destroy the dcdf object
   * 
   */
  ~dcdf();

  int scan_plugin(std::string path = "");

  /**
   * @brief 开始该模块
   * 
   * @return int 
   */
  int start();

  /**
   * @brief 停止该模块
   * 
   * @return int 
   */
  int stop();

  /**
   * @brief 增加数据观察者
   * 
   * @param obs 
   */
  void attach(std::shared_ptr<ge_obs_sample_result> obs);

  /**
   * @brief 删除数据观察者
   * 
   * @param obs 
   */
  void detach(std::shared_ptr<ge_obs_sample_result> obs);

  /**
   * @brief 增加数据观察者
   * 
   * @param obs 
   */
  void attach(std::shared_ptr<ge_obs_batch_result> obs);

  /**
   * @brief 删除数据观察者
   * 
   * @param obs 
   */
  void detach(std::shared_ptr<ge_obs_batch_result> obs);

 private:
  void notify_sresults(std::unique_ptr<algorithm::result> pres);
  void notify_bresults(algorithm::result bres);
  void handle_dcdf_frame(generator::dcdf_frame f);
  void handle_dcdf_status(generator::dcdf_status s);
  void process_entity();

 private:
  std::shared_ptr<dcdf_fobs> m_dcdf_fobs;
  std::shared_ptr<dcdf_sobs> m_dcdf_sobs;
  std::shared_ptr<generator::dcdf_engine> m_dcdf_engine;
  /// 设备序号
  std::string m_dev_id;
  /// 样本序号
  bool update_sid;
  std::string m_sid;
  bool m_run;
  /// 算法处理线程池 - 使用线程池会导致内存泄露 -> 算法插件问题！
  // boost::asio::thread_pool m_tpool;
  /// 算法插件
  boost::shared_ptr<algorithm::graineval_api> m_ge;
  /// 算法结果
  std::unique_ptr<algorithm::result> m_pres;
  /// 算法后处理
  std::atomic<bool> m_post_proc;
  /// 待处理的批样本数
  std::atomic<std::uint32_t> m_remain_batch;
  /// 算法处理线程
  std::thread m_proc_thread;
  /// 待处理批样本信号量
  boost::interprocess::interprocess_semaphore m_sem_data;
  /// 批样本数据池
  std::queue<algorithm::batch_data> m_bdata;
  std::list<std::shared_ptr<ge_obs_sample_result>> m_sres_obs;
  std::list<std::shared_ptr<ge_obs_batch_result>> m_bres_obs;
};

}  // namespace algorithm

#endif  // ALGORITHM_GRAINEVAL_DCDF_H_
