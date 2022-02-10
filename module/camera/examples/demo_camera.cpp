/**
 * @file demo_camera.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <cstdio>
#include <ostream>
#include <thread>
#include <png.h>
#include "module/camera/driver.h"
#include "module/camera/camera.h"
#include "module/camera/common.h"


int write_png(FILE* fp,
                    unsigned int height,
                    unsigned int width,
                    int bytes_per_pixel,
                    unsigned char* data) {
  png_structp _png_ptr;
  png_infop   _info_ptr;

  _png_ptr = png_create_write_struct(
    png_get_libpng_ver(NULL), NULL, NULL, NULL);
  if (!_png_ptr) {
    printf("png_create_write_struct: failed\n");
    return 2;
  }

  _info_ptr = png_create_info_struct(_png_ptr);
  if (!_info_ptr) {
    png_destroy_write_struct(&_png_ptr, NULL);
    printf("png_create_info_struct: failed\n");
    return 2;
  }

  if (setjmp(png_jmpbuf(_png_ptr))) {
    png_destroy_write_struct(&_png_ptr, &_info_ptr);
    printf("setjmp: failed\n");
    return 3;
  }

  png_init_io(_png_ptr, fp);
  png_set_IHDR(_png_ptr, _info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  // source data format was BGR
  png_set_bgr(_png_ptr);
  png_write_info(_png_ptr, _info_ptr);
  png_set_packing(_png_ptr);

  if (height > PNG_SIZE_MAX / (width * bytes_per_pixel))
    png_error(_png_ptr, "Image data buffer would be too large");

  png_bytep* row_pointers = new png_bytep[height];

  if (height > PNG_UINT_32_MAX / (sizeof(png_bytep)))
    png_error(_png_ptr, "Image is to tall to process in memory");

  int k = 0;
  for (k = 0; k < height; ++k)
    row_pointers[k] = data + k * width * bytes_per_pixel;

  png_write_image(_png_ptr, row_pointers);
  png_write_end(_png_ptr, _info_ptr);
  png_destroy_write_struct(&_png_ptr, &_info_ptr);
  delete [] row_pointers;
  return 0;
}

void bgr2rgb(unsigned char* bgr, unsigned int height, unsigned int width) {
  unsigned char* pdata = bgr;
  for (int h = 0; h < height; ++h) {
    for (int w = 0; w < width; ++w, pdata += 3) {
      char tmp = bgr[0];
      pdata[0] = pdata[2];
      pdata[2] = tmp;
    }
  }
}

class cam_comp : public camera::component_observer {
 public:
    void notify_detect(std::shared_ptr<camera::camera> cam) override {
        std::cout << "detect: " << cam->ip() << std::endl;
    }
    void notify_remove(std::shared_ptr<camera::camera> cam) override {
        std::cout << "remove: " << cam->ip() << std::endl;
    }
} cc;

// 上相机
class upcam : public camera::camera_observer {
 public:
    // explicit upcam(std::shared_ptr<camera::camera> pcam) : pcam(pcam) {}
    void handle_frame(camera::frame frame) override {
       if (frame.w == 0 || frame.h == 0 || !frame.data) {
            // std::cout << "Up camera timerout" << std::endl;
            count++;
            // return;
        }
        std::cout << "[" << frame.uid << "]: " << count << " frame(s) lost" << std::endl;
        /* std::string im_name = std::to_string(fid++) + "_u.png";
        FILE* pFile = fopen(im_name.c_str(), "wb");
        write_png(pFile, frame.h, frame.w, 3, (unsigned char*)frame.data.get());
        fclose(pFile); */
    }
 private:
    std::uint32_t fid = 0;
    std::uint32_t count = 0;
    // std::shared_ptr<camera::camera> pcam;
} upc;

// 下相机
class dncam : public camera::camera_observer {
 public:
    // explicit dncam(std::shared_ptr<camera::camera> pcam) : pcam(pcam) {}
    void handle_frame(camera::frame frame) override {
        if (frame.w == 0 || frame.h == 0 || !frame.data) {
            // std::cout << "Down camera timerout" << std::endl;
            count++;
            // return;
        }
        std::cout << "[" << frame.uid << "]: " << count << " frame(s) lost" << std::endl;
        /* std::string im_name = std::to_string(fid++) + "_d.png";
        FILE* pFile = fopen(im_name.c_str(), "wb");
        write_png(pFile, frame.h, frame.w, 3, (unsigned char*)frame.data.get());
        fclose(pFile); */
    }
 private:
    std::uint32_t fid = 0;
    std::uint32_t count = 0;
    // std::shared_ptr<camera::camera> pcam;
} dnc;

int main() {
    auto cam_driver = camera::driver::instance();
    cam_driver->attach(std::make_shared<cam_comp>(cc));
    // 扫描相机 std::unordered_map<std::string, std::shared_ptr<camera::camera>>
    auto cameras = cam_driver->scan_camera();
    if (0 == cameras.size()) {
      std::cout << "No camera found" << std::endl;
      return 0;
    }
    std::shared_ptr<camera::camera> one;
    std::shared_ptr<camera::camera> two;
    for (auto& iter : cameras) {
        if (iter.second->ip() == "223.254.1.1") {
            iter.second->attach(std::make_shared<upcam>(upc));
            one = iter.second;
        }

        if (iter.second->ip() == "223.254.2.1") {
            iter.second->attach(std::make_shared<dncam>(dnc));
            // cam_driver->remove_camera(iter.first);
            two = iter.second;
        }
        // 设置硬触发
        iter.second->trigger_mode(camera::t_trig_mode::software);
        // 开始相机
        iter.second->start();
    }
    while (true) {
      if (one) one->trigger(800);
      if (two) two->trigger(800);
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // iter.second->trigger();
    std::cout << "\n* Input any char to stop..." << std::endl;
    char eof;
    std::cin >> eof;

    return 0;
}
