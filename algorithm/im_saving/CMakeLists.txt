cmake_minimum_required(VERSION 3.5)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
project(dcdf_save VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

set(DCDF_SAVE_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/dcdf_save.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dcdf_save.h
)

add_library(${PROJECT_NAME} ${DCDF_SAVE_SRC})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${OpenCV_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  Threads::Threads Boost::filesystem ${OpenCV_LIBS} generator calibrate logging)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE $<BOOL:${BUILD_SHARED_LIBS}>
)

add_subdirectory(examples)