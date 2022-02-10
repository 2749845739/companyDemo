#include "BoardInterface.h"

BoardInterface::BoardInterface(){}

bool BoardInterface::findBoard()
{
    auto board_driver = board::driver::instance();
    while (true) {
        auto boards = board_driver->scan_board();
        if(boards.size()>=1){
            for (auto& iter : boards) {
                m_board=iter.second;
                m_boardProperty=std::make_shared<BoardProperty>(m_board);
                return true;
            }
        }else{
            //继续查找板子
            if(CMessageBox::ShowInfo("控制器查找失败是否继续查找", nullptr ,CMessageBox::StandardButton::YesNo)==0){
                return false;
            }else{
                continue;
            }
        }
    }
    return false;
}
