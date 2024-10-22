cmake_minimum_required(VERSION 3.10)

project(VideoCapture)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(headers)

add_executable(main main.cpp src/CustomVideoCapture.cpp)
target_link_libraries(main ${OpenCV_LIBS})