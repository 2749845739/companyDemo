cmake_minimum_required(VERSION 3.5)
if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

project(P600 VERSION 1.0.0 LANGUAGES CXX)

option(WITHOUT_UI "build without ui" OFF)
add_definitions(-DQT_DECLARATIVE_DEBUG)
add_definitions(-DQT_QML_DEBUG)
set(QT_VIRTUALKEYBOARD_DESKTOP_DISABLE OFF)
if (NOT WITHOUT_UI)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTORCC ON)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_BUILD_TYPE DEBUG)

if (MSVC)
  add_definitions(/utf-8)
  add_definitions(-DBOOST_LOG_DYN_LINK)
endif()

find_package(Boost REQUIRED COMPONENTS filesystem)
if (NOT WITHOUT_UI)
  find_package(QT NAMES Qt6 Qt5 COMPONENTS
      Widgets Core Quick Qml Gui Sql PrintSupport Concurrent QuickWidgets Charts REQUIRED)
  find_package(Qt${QT_VERSION_MAJOR} COMPONENTS
      Widgets Core Quick Qml Gui PrintSupport Sql Concurrent QuickWidgets Charts REQUIRED)
endif()

find_package(OpenCV REQUIRED)
find_package(Threads REQUIRED)
find_package(PNG REQUIRED)

add_subdirectory(logging)
add_subdirectory(module)
add_subdirectory(generator)
add_subdirectory(algorithm)
add_subdirectory(calibrate)
add_subdirectory(utils)

if (NOT WITHOUT_UI)
  add_subdirectory(UI/Log4Qt)
  add_subdirectory(UI/qtxlsx)

  set(PROJECT_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/CameraProperty.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/CameraProperty.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/CameraInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/CameraInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/FrameDateCore.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/FrameDateCore.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/FrameDateCore.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/BoardCore/BoardProperty.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/BoardCore/BoardProperty.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/BoardCore/BoardInterface.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/BoardCore/BoardInterface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/dirver/dirver.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/dirver/dirver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/qml.qrc
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/Account.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/Account.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/Login.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/Login.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/Login.ui
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/SqlManager.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/SqlManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/SqlSampleId.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/Account/SqlSampleId.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/RequireImage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/RequireImage.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/ViewProvider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/ViewProvider.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/FlowControl.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/FlowControl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/AbstractCameraState.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/AbstractCameraState.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/CameraTaskWork.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/CameraCore/CameraTaskWork.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CMessageBox.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CMessageBox.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CMessageBox.ui
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/GlobalParameter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/GlobalParameter.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/Gzlogger.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/Logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/Logger.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CustomButton.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CustomButton.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/GKeyBoard.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/GKeyBoard.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CustomSplashScreen.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/common/CustomSplashScreen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/main/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/main/FrameLessView.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/main/FrameLessView.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/TableModel/RecordBaseModel.hpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/TableModel/WheatItem.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/TableModel/WheatItem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/TableModel/RecordWheatModel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/TableModel/RecordWheatModel.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AbstractAlgorithmType.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AbstractAlgorithmType.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithmManager.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithmManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithmDataCore.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithmDataCore.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithmWheat.h
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithmWheat.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithDataPool.cpp
    ${CMAKE_CURRENT_LIST_DIR}/UI/AlgorithmCore/AlgorithDataPool.h
  )

  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

  target_include_directories(${PROJECT_NAME}
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/UI/Account
      ${CMAKE_CURRENT_SOURCE_DIR}/UI/CameraCore
      ${CMAKE_CURRENT_SOURCE_DIR}/UI/dirver
      ${CMAKE_CURRENT_SOURCE_DIR}/UI/common
      ${CMAKE_CURRENT_SOURCE_DIR}/UI/Log4Qt/include
      ${CMAKE_CURRENT_SOURCE_DIR}/UI/main
    PRIVATE
      ${CMAKE_BINARY_DIR}/src/platformtheme
  )

  target_link_libraries(${PROJECT_NAME}
    PRIVATE
      Qt${QT_VERSION_MAJOR}::Widgets
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Quick
      Qt${QT_VERSION_MAJOR}::Qml
      Qt${QT_VERSION_MAJOR}::Gui
      Qt${QT_VERSION_MAJOR}::Sql
      Qt${QT_VERSION_MAJOR}::GuiPrivate
      Qt${QT_VERSION_MAJOR}::PrintSupport
      Qt${QT_VERSION_MAJOR}::Concurrent
      Qt${QT_VERSION_MAJOR}::QuickWidgets
      ${OpenCV_LIBS}
      Boost::filesystem
      ${PNG_LIBRARIES}
      Threads::Threads
      dl
      qtxlsx
      board_module
      camera_module
      generator
      calibrate
      graineval
      dcdf_save
      utils
      logging
      log4qt)
endif()
