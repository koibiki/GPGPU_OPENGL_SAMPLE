cmake_minimum_required(VERSION 3.6.2)
project(gpgpu)

set(CMAKE_CXX_STANDARD 11)

include_directories(./ ./utils)

add_executable(gpgpu main.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)