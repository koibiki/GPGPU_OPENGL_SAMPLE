//
// Created by chengli on 5/30/18.
//

//
// Created by chengli on 5/22/18.
//

#include <GL/glew.h>  //最好放在glut.h前面包含
#include <GL/glut.h>
#include <cv.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


const double xMax = 1;
const double xMin = -1;
const double yMax = 1;
const double yMin = -1;
const double nearDist = 0;
const double farDist = 100;


const double camPosX = 0;
const double camPosY = 0;
const double camPosZ = 0;
const double lookAtX = 0;
const double lookAtY = 0;
const double lookAtZ = -1;
const double upX = 0;
const double upY = 1;
const double upZ = 0;

int width;
int height;

int main(int argc, char **argv) {


//////////////////////
// Create a window. //
//////////////////////


    glutInit(&argc, argv);
    glutCreateWindow("RTT window");  //完成OpenGL初始化，但是窗口并没有显示，要调用glutMainLoop才显示
    glutInitWindowSize(width, height);
    glewInit();


//////////////////////////////////
// Check th framebuffer status. //
//////////////////////////////////


    GLenum status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);


    switch (status) {


        case GL_FRAMEBUFFER_COMPLETE_EXT:
            cout << "GL_FRAMEBUFFER_COMPLETE_EXT!: SUCCESS" << endl << endl;
            break;


        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            cout << "GL_FRAMEBUFFER_UNSUPPORTED_EXT!: ERROR" << endl;
            exit(0);


        default:
            exit(0);


    }
// ID numbers for buffers.
    GLuint fbo; // for 'frame buffer object'
    GLuint rbo; // for 'render buffer object'

// ID numbers for textures.
    GLuint renderTarget;
    GLuint textureID;  //外部加载ID号

// Create buffers.
    glGenFramebuffersEXT(1, &fbo);
    glGenRenderbuffersEXT(1, &rbo);

// Create textures.
    glGenTextures(1, &renderTarget);
    glBindTexture(GL_TEXTURE_2D, renderTarget);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

// Set the render target.
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rbo);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, width, height); //

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, renderTarget, 0);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rbo);

//sphere texture
    Mat mat = imread("../test4/airplane.jpg",CV_LOAD_IMAGE_UNCHANGED); //通过opengcv从磁盘加载图
    cvtColor(mat, mat, CV_BGR2BGRA);
    int i = mat.channels();
    imshow("",mat);
    waitKey(0);
    width = mat.cols;
    height = mat.rows;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, mat.data); //已存入显存


///////////////////
// Render scene. //
///////////////////

// Set the render states.
    glEnable(GL_DEPTH_TEST);
    glDepthMask(1);
    glDepthFunc(GL_LEQUAL);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.0);


    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width, height);  // Viewport transformation

    glMatrixMode(GL_PROJECTION);      // Projection transformation
    glLoadIdentity();
    gluPerspective(90, (float) width / (float) height, 0.1, 100);


    glMatrixMode(GL_MODELVIEW);       // Viewing transformation
    glLoadIdentity();
    gluLookAt(camPosX, camPosY, camPosZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);


    glColor3f(1, 1, 1); // yellow 这里是画四边形
    glTranslatef(0, 0, -60);
    glBegin(GL_QUADS);
    glVertex3f(xMin, yMin, 0);
    glVertex3f(xMax, yMin, 0);
    glVertex3f(xMax, yMax, 0);
    glVertex3f(xMin, yMax, 0);
    glEnd();


    unsigned char *color = new unsigned char[width * height * 4];

    cv::Mat img = cv::Mat::zeros(height, width, CV_8UC3);

    glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);
    glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, img.data);


    


    cv::imshow("result", img);

    waitKey(0);

    imwrite("temp.jpg", img); //保存




    delete[] color;
    glDeleteTextures(1, &renderTarget);

// Delete buffers.
    glDeleteFramebuffersEXT(1, &fbo);
    glDeleteRenderbuffersEXT(1, &rbo);

// Return to rendering to the main framebuffer instead of 'fbo'.
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

    return 0;
}