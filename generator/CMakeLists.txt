cmake_minimum_required(VERSION 3.5)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
project(generator VERSION 0.0.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(SAVE_FC_IM "save flow control images" ON)
option(TEST_READ_IM "Get frame from reading image" OFF)

find_package(OpenCV REQUIRED)

set(DATA_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/dcdf_generator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dcdf_generator.h
  ${CMAKE_CURRENT_SOURCE_DIR}/flow_control.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/flow_control.h
  ${CMAKE_CURRENT_SOURCE_DIR}/flow_state.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/flow_state.h
)

add_library(${PROJECT_NAME} ${DATA_SRC})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<BOOL:${SAVE_FC_IM}>:SAVE_FC_IM>
    $<$<BOOL:${TEST_READ_IM}>:TEST_READ_IM>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  logging board_module camera_module PUBLIC ${OpenCV_LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE $<BOOL:${BUILD_SHARED_LIBS}>
)

add_subdirectory(examples)
