#ifndef BOARDINTERFACE_H
#define BOARDINTERFACE_H
#include "module/board/driver.h"
#include "module/board/board.h"
#include "BoardProperty.h"
#include "CMessageBox.h"
class BoardInterface
{
public:
    explicit BoardInterface();
    bool findBoard();
public:
    std::shared_ptr<BoardProperty> m_boardProperty;
    std::shared_ptr<board::board> m_board;
};

#endif // BOARDINTERFACE_H
