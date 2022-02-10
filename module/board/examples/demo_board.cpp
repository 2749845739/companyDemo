/**
 * @file demo_board.cpp
 * @author junjun dong(dongjunjun@gaozhe.com.cn)
 * @brief 
 * @version 0.1
 * @date 2021-10-12
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

#include "module/board/driver.h"
#include "module/board/board.h"

class board_driver_observer : public board::component_observer {
 public:
    void notify_detect(std::shared_ptr<board::board> comp) override {
        std::cout << "+ board: " << comp->uid() << std::endl;
    }

    void notify_remove(std::shared_ptr<board::board> comp) override {
        std::cout << "- board: " << comp->uid() << std::endl;
    }
} cc;

int main() {
    auto board_driver = board::driver::instance();
    board_driver->attach(std::make_shared<board_driver_observer>(cc));
    auto boards = board_driver->scan_board();
    return 0;
}
