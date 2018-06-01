cmake_minimum_required(VERSION 3.6.2)
project(gpgpu)

set(CMAKE_CXX_STANDARD 11)

include_directories(./ ./utils ./include ./0_intruction ./1_texture_buffer ./2_gpgpu_sample ./3_compute_shader)

#find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

#add_executable(gpgpu main.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu 0_intruction/test0_glsl.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu 0_intruction/test0_glsl_trans_var.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu 1_texture_buffer/read_write_texture.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp )

#add_executable(gpgpu 2_gpgpu_sample/gpu_convolution.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

#add_executable(gpgpu utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp read_pic/test.cpp read_pic/shader.cpp)

add_executable(gpgpu 3_compute_shader/simplecompute.cpp utils/CTimer.cpp utils/CReader.cpp utils/CSystem.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLEW_LIBRARY})