//
// Created by chengli on 18-5-17.
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "utils/CReader.h"
#include "utils/CTimer.h"

#define WIDTH 16
#define HEIGHT 16
#define MASK_RADIUS 2       //掩膜半径

using namespace std;

void initGLSL();

void initFBO(unsigned unWidth, unsigned unHeight);

void initGLUT(int argc, char **argv);

void createTextures();

void setupTexture(const GLuint texID);

void performComputation();

void transferFromTexture(float *data);

void transferToTexture(float *data, GLuint texID);

//纹理标识
GLuint yTexID;
GLuint xTexID;

//GLSL 变量
GLuint glslProgram;
GLuint fragmentShader;
GLint outParam, inParam, radiusParam;

//FBO 标识符
GLuint fb;

//"屏幕外窗口"的标识符， 用创建一个有效的OpenGL环境
GLuint glutWindowHandle;

//为OpenGL纹理准备的结构体, 包含了纹理格式,内部格式等
struct structTextureParameters {
    GLenum texTarget;
    GLenum texInternalFormat;
    GLenum texFormat;
    char *shader_source;
} textureParameters;


//全局变量
float *pfInput;
float *pfOutput;
auto fRadius = (float) MASK_RADIUS;
unsigned unWidth = (unsigned) WIDTH;
unsigned unHeight = (unsigned) HEIGHT;
unsigned unSize = unWidth * unHeight;

int main(int argc, char **argv) {
    //生成输入数据
    unsigned unNoData = 4 * unSize;
    pfInput = new float[unNoData];
    pfOutput = new float[unNoData];
    for (unsigned i = 0; i < unNoData; i++) {
        pfInput[i] = i + 1.23;
        std::cout << "input:" << pfInput[i] << endl;
    }



    //确定纹理参数
    textureParameters.texTarget = GL_TEXTURE_RECTANGLE_ARB;
    textureParameters.texInternalFormat = GL_RGBA32F_ARB;
    textureParameters.texFormat = GL_RGBA;

    CReader reader;

    //初始化 GLUT 和 GLEW
    initGLUT(argc, argv);
    glewInit();

    //初始化FBO
    initFBO(unWidth, unHeight);

    //为输入\ 输出数据创建纹理缓存
    createTextures();

    //安全起见 先清除输入纹理缓存
    char f_clean[] = "../test2/clean.frag";
    textureParameters.shader_source = reader.textFileRead(f_clean);
    initGLSL();
    performComputation();

    //计算二位离散卷积
//    char f_convolution[] = "../test2/convolution.frag";
//    textureParameters.shader_source = reader.textFileRead(f_convolution);
//    initGLSL();
//    performComputation();

    //读回计算结果
    transferFromTexture(pfOutput);

    for (unsigned i = 0; i < unNoData; i++) {
        std::cout << "output:" << pfOutput[i] << endl;
    }

    //清理工作
    glDetachShader(glslProgram, fragmentShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(glslProgram);

    glDeleteFramebuffersEXT(1, &fb);
    glDeleteTextures(1, &yTexID);
    glDeleteTextures(1, &xTexID);
    glutDestroyWindow(glutWindowHandle);

    //退出
    delete (pfInput);
    delete (pfOutput);
    return EXIT_SUCCESS;
}

/*
 * 初始化GLUT, 创建的窗口是一个有效的OpenGL环境
 * */
void initGLUT(int argc, char **argv) {
    glutInit(&argc, argv);
    glutWindowHandle = glutCreateWindow("GPGPU Tutorial");
}

/*
 * 屏幕外渲染
 * */
void initFBO(unsigned unWidth, unsigned unHeight) {
    // 创建FBO 准备屏幕外帧缓存
    glGenFramebuffersEXT(1, &fb);

    //绑定屏幕外帧缓存 即避开窗口系统默认的渲染目标
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
    glBindRenderbuffer()

    //设置一个1:1等大的纹理元 像素映射
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, unWidth, 0.0, unHeight);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, unWidth, unHeight);
}

/*
 * 初始化 GLSL 运行时组件 并创建着色器
 * */
void initGLSL() {
    //建立程序对象
    glslProgram = glCreateProgram();

    //建立片段着色器对象
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER_ARB);

    //为着色器设置着色器程序文件
    const GLchar *source = textureParameters.shader_source;
    glShaderSource(fragmentShader, 1, &source, nullptr);

    //编译着色器
    glCompileShader(fragmentShader);

    //把着色器与程序关联
    glAttachShader(glslProgram, fragmentShader);

    //链接到完整的程序 这里使用了默认功能的着色器的顶点着色器 也可以自定义流经顶点着色器
    glLinkProgram(glslProgram);

    //获得 uniform 变量的位置
//    radiusParam = glGetUniformLocation(glslProgram, "fRadius");
}

/*
 * 创建纹理
 * */
void createTextures() {
    // 创建纹理 y保存输出数据 x保存输入数据
    glGenTextures(1, &yTexID);
    glGenTextures(1, &xTexID);

    //配置纹理
    setupTexture(yTexID);
    setupTexture(xTexID);
    transferToTexture(pfInput, xTexID);

    //设定映射参数 使写入目标缓存的数据覆盖原来的数据
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

/*
 * 设置纹理参数为最近点采样和边缘钳制 并设置纹理的数据类型为单精度浮点数
 * */
void setupTexture(const GLuint texID) {
    //激活并绑定将要设置的纹理
    glBindTexture(textureParameters.texTarget, texID);

    //关闭滤波算法和边界以外的重复算法
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(textureParameters.texTarget, GL_TEXTURE_WRAP_T, GL_NEAREST);

    //定义纹理的数据类型为float
    glTexImage2D(textureParameters.texTarget, 0, textureParameters.texInternalFormat, unWidth, unHeight, 0,
                 textureParameters.texFormat, GL_FLOAT, 0);
}

void performComputation() {
    //关联输出缓存到FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, textureParameters.texTarget, yTexID, 0);

    //将glslProgram设为当前程序
    glUseProgram(glslProgram);

    //将GL_TEXTURE0 设为当前纹理单元
    glActiveTexture(GL_TEXTURE0);
    //更新 uniform变量 将应用程序的fRadius的值传递给着色器内部
//    glUniform1f(radiusParam, fRadius);

    //线程同步 方便计时
    glFinish();

    CTimer timer;
    long lTime;

    timer.reset();

    //设置写入纹理缓存的类型
    glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

    //将计算范围定义为同样包括矩形的内部
    glPolygonMode(GL_FRONT, GL_FILL);

    //用未归一化的纹理坐标设定计算范围
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(0.0, 0.0);
    glTexCoord2f(unWidth, 0.0);
    glVertex2f(unWidth, 0.0);
    glTexCoord2f(unWidth, unHeight);
    glVertex2f(unWidth, unHeight);
    glTexCoord2f(0.0, unHeight);
    glVertex2f(0.0, unHeight);

    //同步线程 终止计算
    glFinish();
    lTime = timer.getTime();
    cout << "Time elapsed:" << lTime << " ms." << endl;
}

/*
 * 将数据从当前纹理缓存传至主存储器
 * */
void transferFromTexture(float *data) {
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadPixels(0, 0, unWidth, unHeight, textureParameters.texFormat, GL_FLOAT, data);
}

/*
 * 将数据传至纹理缓存 注意在使用硬件加速时ati和nvidia的区别
 * */
void transferToTexture(float *data, GLuint texID) {
    glBindTexture(textureParameters.texTarget, texID);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, textureParameters.texTarget, texID, 0);
    glTexSubImage2D(textureParameters.texTarget, 0, 0, 0, unWidth, unHeight, textureParameters.texFormat, GL_FLOAT,
                    data);
}