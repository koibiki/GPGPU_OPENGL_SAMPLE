//
// Created by chengli on 18-5-17.
//
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>


#define WIDTH 2         //数据矩阵的宽
#define HEIGHT 3        //数据矩阵的高

using namespace std;

int main(int argc, char **argv) {
    auto nWidth = (int) WIDTH;
    auto nHeight = (int) HEIGHT;
    int nSize = nWidth * nHeight;

    //创建输入数据
    auto *pfInput = new float[4 * nSize];
    auto *pfOutput = new float[4 * nSize];
    for (int i = 0; i < nSize * 4; i++) {
        pfInput[i] = i + 1.2345f;
    }

    //设定GLUT,创建新窗口, 以便有一个有效的OpenGL环境
    //然后取得OpenGL扩展的入口
    glutInit(&argc, argv);
    glutCreateWindow("GPGPU Tutorial");
    glewInit();

    //创建FBO并绑定
    GLuint fb;
    glGenFramebuffersEXT(1, &fb);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);

    //创建纹理对象并绑定
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    //设置纹理参数
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    //将纹理关联到FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, tex, 0);


    //将纹理数据类型定义为单精度浮点数
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA_FLOAT32_ATI, nWidth, nHeight, 0, GL_RGBA, GL_FLOAT, nullptr);

    //将数据传至纹理缓存
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, nWidth, nHeight, GL_RGBA, GL_FLOAT, pfInput);

    //读回
    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadPixels(0, 0, nWidth, nHeight, GL_RGBA, GL_FLOAT, pfOutput);

    //打印并检查结果
    bool bCmp = true;
    for (int i = 0; i < nSize * 4; i++) {
        cout << i << ":\t" << pfInput[i] << '\t' << pfOutput[i] << endl;
        if (pfInput[i] != pfOutput[i]) {
            bCmp = false;
        }
    }

    if (bCmp) {
        cout << "Round trip complete" << endl;
    } else {
        cout << "Round trip failed" << endl;
    }

    //清理, 返回
    delete (pfInput);
    delete (pfOutput);
    glDeleteFramebuffersEXT(1, &fb);
    glDeleteTextures(1, &tex);

    return 0;
}
