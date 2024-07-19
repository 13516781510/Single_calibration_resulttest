cmake_minimum_required(VERSION 3.28)
project(singlecalibrationresulttest)

set(CMAKE_CXX_STANDARD 17)
#只和cv的配置有关
if(NOT OpenCV_DIR)
    set(OpenCV_DIR D:/opencv/opencv/mingwbuild)
endif()
message(STATUS "OpenCV_DIR = ${OpenCV_DIR}")
find_package(OpenCV REQUIRED)
set( EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable(singlecalibrationresulttest main.cpp CameraParams.h)

target_include_directories(singlecalibrationresulttest PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(singlecalibrationresulttest PRIVATE ${OpenCV_LIBS})
