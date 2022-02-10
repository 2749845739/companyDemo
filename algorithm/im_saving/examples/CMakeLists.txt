find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(demo_imsave EXCLUDE_FROM_ALL
    demo_imsave.cpp
)
target_include_directories(demo_imsave PRIVATE
    ${PNG_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(demo_imsave PRIVATE
    ${PNG_LIBRARIES} ${OpenCV_LIBS} Threads::Threads generator dcdf_save board_module camera_module logging)
