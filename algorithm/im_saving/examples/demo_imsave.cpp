/**
 * @file demo_dimsave.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-21
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

#include "generator/dcdf_generator.h"
#include "generator/flow_control.h"
#include "module/camera/driver.h"
#include "module/board/driver.h"
#include "algorithm/im_saving/dcdf_save.h"
#include "logging/log.h"
#include "module/def.h"

// #define UP_CAM_IP "223.254.1.1"
// #define DN_CAM_IP "223.254.2.1"
// #define FC_CAM_IP "223.254.3.1"

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

  if (!up_cam || !dn_cam || !pboard) {
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
  dn_cam->hflip(true);

  std::shared_ptr<generator::dcdf_engine> pengine =
    std::make_shared<generator::dcdf_engine>(pboard, up_cam, dn_cam, GT_WHEAT, WHEAT_HH);
  pengine->start();
  algorithm::dcdf_save imsave(pengine, nullptr, "./imsave/", "21-GQ-P600-8888");
  imsave.enable();
  pboard->start_task();
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  pboard->vibrator_sample_ready(0, 0);

  std::cout << "input any char to send stop task to board" << std::endl;
  char c;
  std::cin >> c;
  pboard->stop_task();
  std::cout << "input any char to stop...." << std::endl;
  char d;
  std::cin >> d;
  pboard->vibrator_sample_ready(0, 1);

  return 0;
}
