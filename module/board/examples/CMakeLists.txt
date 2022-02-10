add_executable(demo_board EXCLUDE_FROM_ALL
    demo_board.cpp
)
target_include_directories(demo_board PRIVATE
    ${PNG_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(demo_board PRIVATE board_module)
