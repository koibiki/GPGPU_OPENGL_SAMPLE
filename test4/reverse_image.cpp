#include <GL/glut.h>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

int mWidth;
int mHeight;

//设置图像指针
GLubyte *pixels;


void display() {
    // 清除屏幕
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //像素读图
    glDrawPixels(mWidth, mHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
    //双缓存交换缓存以显示图像
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    //获取图像指针函数
//    Mat I = imread("../test4/airplane.jpg");
    Mat I = imread("../test4/sample.bmp");


    int width = I.cols;
    int height = I.rows;
    mWidth = width;
    mHeight = height;

    //OpenCV显示
    imshow("OpenCV", I);
    //图像翻转
    flip(I, I, 0);
    imshow("OpenCV flip", I);
    //设置指针长度
    int pixellength = width * height * 4;
    //开辟指针空间
    pixels = new GLubyte[pixellength];
    //图像指针复制
    memcpy(pixels, I.data, pixellength * sizeof(char));
    //初始化GL
    glutInit(&argc, argv);
    //设置显示参数(双缓存，RGB格式)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    //设置窗口尺寸：width*height
    glutInitWindowSize(width, height);
    //设置窗口尺寸为固定值：400*400
    //glutInitWindowSize(400, 400);
    //设置窗口位置：在屏幕左上角像素值(100,100)处
    glutInitWindowPosition(100, 100);
    //设置窗口名称
    glutCreateWindow("OpenGL");
    //显示函数，display事件需要自行编写
    glutDisplayFunc(display);

    //重复循环GLUT事件
    glutMainLoop();
    //OpenGL循环结束后释放图像指针内存
    free(pixels);
    return 0;
}