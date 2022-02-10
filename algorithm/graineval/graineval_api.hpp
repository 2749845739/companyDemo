/**
 * @file graineval_api.hpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-11-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef INTERFACE_GRAINEVAL_API_HPP_
#define INTERFACE_GRAINEVAL_API_HPP_

#include <string>
#include <vector>
#include <memory>
#include <utility>

#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/dll/import.hpp>
#include <boost/config.hpp>
#include <boost/function.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

#include "opencv2/opencv.hpp"

#define GRAINEVAL_CREATOR_SYMBOL "create_graineval"

namespace algorithm {

enum class wheat_t : std::uint8_t {
  zc = 0,   // 正常粒
  bb,       // 病斑粒(大类，包含例如赤霉，黑胚等多种子类)
  sy,       // 生芽粒
  sm,       // 生霉粒
  cs,       // 虫蚀粒
  ps,       // 破损粒
  hp,       // 黑胚粒(隶属于病斑粒)
};

enum class rice_t : std::uint8_t {
  zc = 0,   // 正常粒
  hl,       // 黄粒米
  ps,       // 破损粒
};

struct batch_data {
  /// 采集设备序号
  std::string dev_str;
  /// 批样本序号
  std::uint32_t id;
  /// 批样本质量
  float wei;
  /// 样本采集时间
  std::string time_str;
  /// 样本谷物类型
  std::string grain_str;
  /// 样本不完善粒类型
  std::string unsound_str;
  /// 样本采集的图像数据
  std::vector<std::shared_ptr<cv::Mat>> data;
};

struct result {
  /********** 每批次数据 **********/
  /// 批次样本重量
  std::vector<float> weights;
  /// 批次样本中颗粒长度
  std::vector<float> lengths;
  /// 批次样本中颗粒宽度
  std::vector<float> widths;
  /// 批次样本中颗粒长宽比
  std::vector<float> aspect_ratio;
  /// 批次样本中颗粒周长
  std::vector<float> perimeter;
  /// 批次样本中颗粒分割图（A相机反射，B相机反射，A相机透射，B相机透射，A相机Mask，B相机Mask）
  std::vector<std::vector<std::shared_ptr<cv::Mat>>> im_segment;

  /********** 平均值 **********/
  /// 平均长度
  float avg_length;
  /// 平均宽度
  float avg_width;
  /// 平均长宽比
  float avg_aspect_ratio;
  /// 平均周长
  float avg_perimeter;

  struct _wheat {
    /// 所有批样本杂质数量
    std::vector<std::vector<int>> impurity_count;
    /// 所有批样本数量
    std::vector<std::vector<int>> unsound_count;
    /// 所有批样本质量
    std::vector<std::vector<float>> unsound_wei;
    // 所有样本softmax prob
    std::vector<std::vector<float>> all_unsound_prob;
    /// 所有不完善粒数量
    std::vector<int> total_unsound_count;
    /// 所有不完善粒质量
    std::vector<float> total_unsound_wei;
    /// 所有白麦质量
    std::vector<float> total_white_wei;
    /// 所有颗粒分类结果
    std::vector<std::pair<wheat_t, float>> recs;
    /// 正常粒和不完善粒的质量比
    std::vector<std::pair<wheat_t, float>> wei_ratio;
    /// 正常粒和不完善粒的颗粒比
    std::vector<std::pair<wheat_t, float>> count_ratio;
    /********** 指标 **********/
    /// 节节麦比例
    float jjm_ratio;
    /// 千粒重
    float thousand_wei;
    /// 容重
    float volume_wei;
    /// 白麦颗粒比例
    float white_count_ratio;
    /// 白麦质量比
    float white_wei_ratio;
    /// 异种粮比例
    float exotic_ratio;
    /// 杂质比例
    float impurity_ratio;
    /// 水份
    float moisture;
  } wheat;

  struct _rice {
    /// 所有批样本破碎数量
    std::vector<int> broken_count;
    /// 所有批样本精米数量
    std::vector<int> whole_count;
    /// 所有批样本黄粒米数量
    std::vector<int> yellow_count;
    /// 所有颗粒分类结果
    std::vector<std::pair<rice_t, float>> recs;
    /// 精米面积
    std::vector<float> whole_area;
    /// 破碎米面积
    std::vector<float> broken_area;
    /// 垩白粒面积
    std::vector<float> chalky_area;
    /********** 指标 **********/
    /// 精米率
    float whole_ratio;
    /// 碎米率
    float broken_ratio;
    /// 黄粒米率
    float yellow_ratio;
    /// 垩白率
    float chalky_ratio;
  } rice;
};

class BOOST_SYMBOL_VISIBLE graineval_api {
 public:
 /**
  * @brief 插件名
  * 
  * @return std::string 
  */
  virtual std::string name() const = 0;

  /**
   * @brief 插件版本信息
   * 
   * @return std::string 版本信息
   */
  virtual std::string version() const = 0;

  /**
   * @brief 数据处理
   * 
   * @param data 输入数据
   * @param res 输出处理结果
   * @return int 
   */
  virtual int process(batch_data data, result* res) = 0;

  /**
   * @brief 数据后处理
   * 
   * @param res 输入/输出数据
   * @return int 
   */
  virtual int post_process(result* res) = 0;
};

}  // namespace algorithm

#endif  // INTERFACE_GRAINEVAL_API_HPP_
