cmake_minimum_required(VERSION 3.5)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
project(board_module VERSION 0.0.4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED filesystem)

set(BOARD_MODULE_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/board_plugin_api.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/board.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/board.h
  ${CMAKE_CURRENT_SOURCE_DIR}/driver.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/driver.h
)

add_library(${PROJECT_NAME} ${BOARD_MODULE_SRC})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${Boost_INCLUDE_DIR}
  PRIVATE ${CMAKE_SOURCE_DIR}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  $<$<NOT:$<BOOL:${MSVC}>>:dl> Boost::filesystem Threads::Threads utils)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  POSITION_INDEPENDENT_CODE $<BOOL:${BUILD_SHARED_LIBS}>
)

add_subdirectory(examples)
