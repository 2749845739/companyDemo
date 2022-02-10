find_package(PNG REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(demo_dcdf EXCLUDE_FROM_ALL
    demo_dcdf.cpp
)
target_include_directories(demo_dcdf PRIVATE
    ${PNG_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo_dcdf PRIVATE
    ${PNG_LIBRARIES} ${OpenCV_LIBS} Threads::Threads generator dcdf_save board_module camera_module)
