find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_executable(demo_calibrate EXCLUDE_FROM_ALL
    demo_calibrate.cpp
)
target_include_directories(demo_calibrate PRIVATE
    ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIR})
target_link_libraries(demo_calibrate PRIVATE Threads::Threads calibrate camera_module board_module)
