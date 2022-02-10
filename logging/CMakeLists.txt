cmake_minimum_required(VERSION 3.5)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
project(logging VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_LOG "open terminal log" ON)
option(LOG_TID "log with thread id" ON)
option(LOG_SCOPE "log with scope" ON)
option(LOG_NOCOLOR "log without color" OFF)

find_package(Boost REQUIRED COMPONENTS log log_setup locale)
find_package(Threads REQUIRED)

set(LOGGING_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/log.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/log.h
)

add_library(${PROJECT_NAME} ${LOGGING_SRC})

target_include_directories(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}
    ${Boost_INCLUDE_DIR}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_compile_definitions(${PROJECT_NAME}
  PUBLIC $<$<BOOL:${LOG_NOCOLOR}>:LOG_NOCOLOR>
  PUBLIC $<$<BOOL:${LOG_TID}>:LOG_TID>
  PUBLIC $<$<BOOL:${LOG_SCOPE}>:LOG_SCOPE>
  PRIVATE $<$<BOOL:${ENABLE_LOG}>:ENABLE_LOG>
)

target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads Boost::log_setup Boost::log Boost::locale)

set_target_properties(${PROJECT_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION_MAJOR}
  # POSITION_INDEPENDENT_CODE $<BOOL:${BUILD_SHARED_LIBS}>
)

add_executable(demo_log EXCLUDE_FROM_ALL demo_log.cpp)
target_link_libraries(demo_log PRIVATE ${PROJECT_NAME})
