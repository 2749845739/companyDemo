find_package(PNG REQUIRED)
add_executable(demo_camera EXCLUDE_FROM_ALL
    demo_camera.cpp
)
target_include_directories(demo_camera PRIVATE
    ${PNG_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
target_link_libraries(demo_camera PRIVATE ${PNG_LIBRARIES} camera_module)
