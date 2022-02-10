/**
 * @file demo_calibrate.cpp
 * @author junjun dong (dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-11-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <ostream>

#include "logging/log.h"
#include "calibrate/calibrate.h"
#include "module/def.h"
#include "module/camera/driver.h"
#include "module/board/driver.h"

boost::log::sources::severity_logger<logging::severity_level> demo_cal_lg;
BOOST_LOG_SCOPED_LOGGER_TAG(demo_cal_lg, "Module", "DEMO_CAL");

int main() {
    // 初始化日志
    logging::logger::init("logs");
    // 查找相机
    auto cam_driver = camera::driver::instance();
    auto cameras = cam_driver->scan_camera();
    std::shared_ptr<camera::camera> up_cam;
    std::shared_ptr<camera::camera> dn_cam;
    for (auto &it : cameras) {
        if (it.second->ip() == UP_CAM_IP) up_cam = it.second;
        if (it.second->ip() == DN_CAM_IP) dn_cam = it.second;
    }
    // 查找控制板
    auto board_driver = board::driver::instance();
    auto boards = board_driver->scan_board();
    std::shared_ptr<board::board> pbd;
    for (auto &it : boards) {
        pbd = it.second;
        break;
    }

    if (!up_cam || !dn_cam || !pbd) {
        BOOST_LOG_SEV(demo_cal_lg, logging::FATAL) << "components not ready";
        return -1;
    }

    calibrate::calibrator cal(up_cam, dn_cam, pbd, GT_WHEAT, WHEAT_HH);

    int cmd;
    bool is_start = false;
    bool is_ulight = false;
    bool is_dlight = false;
    bool is_inturn = false;
    while (true) {
        std::cout << "[main] 请选择：[1] 开始 [2] 上光源 [3] 下光源 [4] 循环 [5] 暂停 [6] 停止 [0] 退出 ";
        std::flush(std::cout);
        std::cin >> cmd;
        switch (cmd) {
            case 0: return 0;

            case 1:
            cal.run(true);
            is_start = true;
            break;

            case 2:
            cal.ulight(true);
            is_ulight = true;
            break;

            case 3:
            cal.dlight(true);
            is_dlight = true;
            break;

            case 4:
            cal.inturn(true);
            is_inturn = true;
            break;

            case 5:
            if (is_start) {
                cal.run(false);
                is_start = false;
            }
            if (is_ulight) {
                cal.ulight(false);
                is_ulight = false;
            }
            if (is_dlight) {
                cal.dlight(false);
                is_dlight = false;
            }
            if (is_inturn) {
                cal.inturn(false);
                is_inturn = false;
            }
            break;

            case 6:
            if (is_start) {
                cal.run(false);
                is_start = false;
            }
            if (is_ulight) {
                cal.ulight(false);
                is_ulight = false;
            }
            if (is_dlight) {
                cal.dlight(false);
                is_dlight = false;
            }
            if (is_inturn) {
                cal.inturn(false);
                is_inturn = false;
            }
            cal.stop();
            break;

            default: break;
        }
    }

    return 0;
}
