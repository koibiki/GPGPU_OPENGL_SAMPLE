//
// Created by chengli on 5/23/18.
//

#ifndef GPGPU_SHADER_H
#define GPGPU_SHADER_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <opencv2/opencv.hpp>

void InitializeGeometry(GLuint program_id);

GLuint LoadImage(cv::Mat mat);
GLuint ShaderProgram(const std::string &vertex_shader_file, const std::string &fragment_shader_file);
#endif //GPGPU_SHADER_H
