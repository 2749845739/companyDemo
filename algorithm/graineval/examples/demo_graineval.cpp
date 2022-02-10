/**
 * @file demo_graineval.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-11-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <chrono>
#include <exception>
#include <regex>
#include <string>
#include <sstream>
#include <thread>

#include "logging/log.h"
#include "generator/dcdf_generator.h"
#include "generator/flow_control.h"
#include "module/def.h"
#include "module/camera/driver.h"
#include "module/board/driver.h"
#include "algorithm/im_saving/dcdf_save.h"
#include "algorithm/graineval/dcdf.h"

#include <boost/dll/shared_library.hpp>
#include <boost/dll/shared_library_load_mode.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/directory.hpp>
#include <boost/filesystem/exception.hpp>
#include <boost/filesystem/file_status.hpp>

#define ALG_PLUGIN_NAME "algorithm_p600"
#define ALG_PLUGIN_PATH "graineval_plugin"

#define DEVICE_ID "21-GQ-P600-1234"
#define SAVE_PATH "./original/"
#define FC_TEMPLATE "./flowmodel/fc_template.png"

boost::log::sources::severity_logger<logging::severity_level> demoai_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(demoai_lg, "Module", "DEMOAI");

typedef boost::shared_ptr<algorithm::graineval_api>(create_t)();

class dcdf_obs : public generator::dcdf_obs_frame {
 public:
  explicit dcdf_obs(std::function<void(generator::dcdf_frame frame)> frame_cb) : m_cb(frame_cb) {}
  void handle_frame(generator::dcdf_frame frame) override {
    if (m_cb) m_cb(frame);
  }

 private:
  std::function<void(generator::dcdf_frame frame)> m_cb;
};

#ifndef DEMO_BY_FILES
int main() {
  logging::logger::init();

  auto cam_driver = camera::driver::instance();
  auto cameras = cam_driver->scan_camera();
  std::shared_ptr<camera::camera> up_cam;
  std::shared_ptr<camera::camera> dn_cam;
  std::shared_ptr<camera::camera> fc_cam;
  for (auto &it : cameras) {
    if (it.second->ip() == UP_CAM_IP) { up_cam = it.second; }
    if (it.second->ip() == DN_CAM_IP) { dn_cam = it.second; }
    if (it.second->ip() == FC_CAM_IP) { fc_cam = it.second; }
  }

  auto board_driver = board::driver::instance();
  auto boards = board_driver->scan_board();
  std::shared_ptr<board::board> pboard;
  for (auto &it : boards) {
    pboard = it.second;
    break;
  }

  if (!up_cam || !dn_cam || !fc_cam || !pboard) {
    std::cerr << "Err: components not ready" << std::endl;
    return -1;
  }
  pboard->capture_delay(10);

  // 配置相机
  up_cam->rgain(2100);
  up_cam->ggain(1000);
  up_cam->bgain(1800);

  dn_cam->rgain(2100);
  dn_cam->ggain(1000);
  dn_cam->bgain(1800);

  fc_cam->rgain(2200);
  fc_cam->ggain(1050);
  fc_cam->bgain(1850);
  fc_cam->exposure_time(400);

  std::shared_ptr<generator::dcdf_engine> pengine =
    std::make_shared<generator::dcdf_engine>(pboard, up_cam, dn_cam, GT_WHEAT, WHEAT_HH);

  algorithm::dcdf dcdf_ge(pengine, DEVICE_ID);
  if (dcdf_ge.scan_plugin() < 0) {
    BOOST_LOG_SEV(demoai_lg, logging::FATAL) << "scan plugin failed";
    return -1;
  }
  dcdf_ge.start();

  algorithm::dcdf_save imsave(pengine, nullptr, SAVE_PATH, DEVICE_ID);
  pengine->start();
  imsave.enable();
  auto fcon = std::make_shared<generator::flow_control>(
      fc_cam, pboard, FC_TEMPLATE, 82, 800, 75, 25, 10);
  fcon->init_state();
  fcon->run();
  std::cout << "input `c' to run, input `q' to exit" << std::endl;
  while (true) {
    char c;
    if (!(std::cin >> c)) {
      std::cin.clear();
      continue;
    }
    if (c == 'q') {
      break;
    } else if (c == 'c') {
      fcon->run();
    }
  }
  dcdf_ge.stop();
  return 0;
}
#else
int main(int argc, char** argv) {
  logging::logger::init("logs");

  if (argc != 2) {
    BOOST_LOG_SEV(demoai_lg, logging::FATAL) << "Usage: " << argv[0] << " [im path]";
    return -1;
  }

  // 列出目标目录下所有文件
  boost::filesystem::path p(argv[1]);
  std::vector<boost::filesystem::path> v;
  try {
    if (boost::filesystem::is_directory(p)) {
      BOOST_LOG_SEV(demoai_lg, logging::INFO) << p;
      for (auto&& x : boost::filesystem::directory_iterator(p)) {
        // BOOST_LOG_SEV(demoai_lg, logging::INFO) << x.path();
        v.push_back(x.path());
      }
      std::sort(v.begin(), v.end());
    } else {
      BOOST_LOG_SEV(demoai_lg, logging::FATAL) << "Err: input im path is not a director";
      return -2;
    }
  } catch (const boost::filesystem::filesystem_error& e) {
    BOOST_LOG_SEV(demoai_lg, logging::FATAL) << "Err: exception -> " << e.what();
    return -3;
  }

  // 寻找插件
  auto lib_path = boost::dll::fs::path(ALG_PLUGIN_PATH) / ALG_PLUGIN_NAME;
  boost::shared_ptr<algorithm::graineval_api> plib;
  try {
    boost::dll::shared_library lib(lib_path, boost::dll::load_mode::append_decorations);
    // 没有symbol
    if (!lib.has(GRAINEVAL_CREATOR_SYMBOL)) return -1;
    plib = boost::dll::import_alias<create_t>(boost::move(lib), GRAINEVAL_CREATOR_SYMBOL)();
  } catch (std::exception e) {
    // 库文件/库目录不存在
    return -2;
  }
  std::cout << plib->name() << ", ver: " << plib->version() << std::endl;
  // 1: head, 7: tail
  // 2: dev_str, 3: time_str, 4: id, 5: grain_type, 6: abnomal_type, 8: wei
  std::regex name_pattern(
    "((\\d{2}-[A-Z]{2}-[A-Z]{1,3}\\d{2,4}-\\d{4})_\\d{1}_(\\d{14})_(\\d{1,3})_(\\d{2})_(\\d{2})_[.+_]?)"
    "UA"
    "(_(\\d{1,2}.\\d{3})\\..{3,4}$)");

  algorithm::result res;
  int xi = 0;
  // 处理文件
  for (auto&& x : v) {
    std::smatch tmatch;
    std::string im_name = x.filename().native();
    if (std::regex_match(im_name, tmatch, name_pattern)) {
      // for (int i = 0; i < tmatch.size(); ++i) {
      //   std::cout  << i << ": " << tmatch[i] << std::endl;
      // }
      std::string ua_name = (p / im_name).native();
      std::string ub_name = (p / (tmatch[1].str() + "UB" + tmatch[7].str())).native();
      std::string da_name = (p / (tmatch[1].str() + "DA" + tmatch[7].str())).native();
      std::string db_name = (p / (tmatch[1].str() + "DB" + tmatch[7].str())).native();
      // BOOST_LOG_SEV(demoai_lg, logging::INFO) << "path: " << p
      //   << ", image names: " << ua_name << "\n\t"
      //   << ub_name << "\n\t" << da_name << "\n\t" << db_name;
      std::shared_ptr<cv::Mat> im_ua = std::make_shared<cv::Mat>(cv::imread(ua_name));
      std::shared_ptr<cv::Mat> im_ub = std::make_shared<cv::Mat>(cv::imread(ub_name));
      std::shared_ptr<cv::Mat> im_da = std::make_shared<cv::Mat>(cv::imread(da_name));
      std::shared_ptr<cv::Mat> im_db = std::make_shared<cv::Mat>(cv::imread(db_name));
      if (!im_ua->data) {
        BOOST_LOG_SEV(demoai_lg, logging::FATAL) << "Err: UA image(" << ua_name << ") read failed";
        return -3;
      }
      if (!im_ub->data) {
         BOOST_LOG_SEV(demoai_lg, logging::MINOR) << "War: UB image(" << ub_name << ") read failed";
         im_ub = std::make_shared<cv::Mat>(im_ua->clone());
      }
      if (!im_da->data) {
        BOOST_LOG_SEV(demoai_lg, logging::FATAL) << "Err: DA image(" << da_name << ") read failed";
        return -4;
      }
      if (!im_db->data) {
         BOOST_LOG_SEV(demoai_lg, logging::MINOR) << "War: DB image(" << db_name << ") read failed";
         im_db = std::make_shared<cv::Mat>(im_da->clone());
      }
      xi++;

      int id = 0;
      std::istringstream(tmatch[4]) >> id;
      float wei = 0.f;
      std::istringstream(tmatch[8]) >> wei;
      // BOOST_LOG_SEV(demoai_lg, logging::INFO) << "dev: " << tmatch[2] << ", time: " << tmatch[3]
      //   << ", id: " << id << ", grain: " << tmatch[5] << ", unsound: " << tmatch[6] << ", wei: " << wei;
      // 调用算法
      plib->process({tmatch[2],
        static_cast<uint32_t>(id),
        wei, tmatch[3], tmatch[5], tmatch[6],
        {im_ua, im_ub, im_da, im_db}}, &res);
      res.weights.push_back(10.5 * xi + 7.8);
    }
  }
  plib->post_process(&res);

  std::cout << "input any char to stop...." << std::endl;
  char c;
  std::cin >> c;

  return 0;
}

#endif  // DEMO_BY_FILES
