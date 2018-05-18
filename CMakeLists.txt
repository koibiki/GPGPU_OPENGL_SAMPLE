cmake_minimum_required(VERSION 3.6.2)
project(gpgpu)

set(CMAKE_CXX_STANDARD 11)

include_directories(./ ./utils)

find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

#add_executable(gpgpu main.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu test0/test0_glsl.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu test0/test0_glsl_trans_var.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu test1/read_write_texture.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp )

#add_executable(gpgpu test3/gpu_convolution.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

add_executable(gpgpu test4/reverse_image.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY} ${OpenCV_LIBS})