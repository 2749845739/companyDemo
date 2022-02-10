/**
 * @file demo_dcdf.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <png.h>
#include <type_traits>
#include <condition_variable>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "generator/dcdf_generator.h"
#include "generator/flow_control.h"
#include "module/def.h"
#include "module/camera/driver.h"
#include "module/board/driver.h"
#include "algorithm/im_saving/dcdf_save.h"
#include "logging/log.h"

#define DEVICE_ID "21-GQ-P600-1234"
#define SAVE_PATH "./original/"
#define FC_TEMPLATE "./flowmodel/fc_template.png"

class cam_comp : public camera::component_observer {
 public:
    void notify_detect(std::shared_ptr<camera::camera> cam) override {
        std::cout << "+ camera: " << cam->ip() << std::endl;
    }
    void notify_remove(std::shared_ptr<camera::camera> cam) override {
        std::cout << "- camera: " << cam->ip() << std::endl;
    }
} cc;

class board_comp : public board::component_observer {
 public:
    void notify_detect(std::shared_ptr<board::board> comp) override {
        std::cout << "+ board: " << comp->uid() << std::endl;
    }

    void notify_remove(std::shared_ptr<board::board> comp) override {
        std::cout << "- board: " << comp->uid() << std::endl;
    }
} bc;


int main() {
  logging::logger::init();
  auto cam_driver = camera::driver::instance();
  cam_driver->attach(std::make_shared<cam_comp>(cc));
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
  board_driver->attach(std::make_shared<board_comp>(bc));
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

  // 配置相机
  up_cam->rgain(2100);
  up_cam->ggain(1000);
  up_cam->bgain(1800);

  dn_cam->rgain(2100);
  dn_cam->ggain(1000);
  dn_cam->bgain(1800);

  fc_cam->rgain(2200);
  fc_cam->ggain(1000);
  fc_cam->bgain(1800);
  fc_cam->exposure_time(1000);

  // dcdf_engine engine(pboard, up_cam, dn_cam, GT_WHEAT, WHEAT_HH);
  std::shared_ptr<generator::dcdf_engine> pengine =
    std::make_shared<generator::dcdf_engine>(pboard, up_cam, dn_cam, GT_WHEAT, WHEAT_HH);
  algorithm::dcdf_save imsave(pengine, nullptr, SAVE_PATH, DEVICE_ID);
  pengine->start();
  imsave.enable();
  // engine.attach(std::shared_ptr<dcdf_comp>(new dcdf_comp));
  // engine.start();
  auto fcon = std::make_shared<generator::flow_control>(
      fc_cam, pboard, FC_TEMPLATE, 82, 800, 75, 5, 10);
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

  return 0;
}
