//
// Created by chengli on 5/23/18.
//

#include <stdlib.h>
#include "test6/shader.h"


void show(int height , int width) {
    cv::Mat img = cv::Mat::zeros(height, width, 16);

    //use fast 4-byte alignment (default anyway) if possible
    //glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);

    //set length of one complete row in destination data (doesn't need to equal img.cols)
//glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
    glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);//opencv存储为BGR顺序
    cv::flip(img, img, 0);//需要翻转
    cv::imshow("result", img);
    cv::waitKey(0);

}


int main(int argc, char **argv) {


//1、初始化环境
    glutInit(&argc, argv);
    glutInitWindowSize(512,512);
    glutInitWindowPosition(100,100);
    glutCreateWindow("GLEW Test");
    glewExperimental = GL_TRUE;
    glewInit();
    if (!glewIsSupported("GL_VERSION_4_0")) {
        std::cerr << "Failed to initialize GLEW with OpenGL 4.0!" << std::endl;
        return EXIT_FAILURE;
    }
//2、读取、创建shader程序，编译连接等
    auto program_id = ShaderProgram("../read_pic/gl_texture.vert", "../read_pic/gl_texture.frag");
    glUseProgram(program_id);

    cv::Mat mat = cv::imread("../read_pic/2.jpg");
    int i = mat.type();
    cv::imshow("OpenCV", mat);

//3、设置纹理相关参数、或者输入shader计算所需要的数据
    auto texture_id = LoadImage(mat);//读入一张图片，转成纹理格式，把并把图片数据拷贝到opengl纹理单元。
    auto texture_attrib = glGetUniformLocation(program_id, "Texture");//找到shader程序中，变量名为Texture，类型为uniform的变量索引
//    glUniform1i(texture_attrib, texture_id);
    glActiveTexture(GL_TEXTURE);//启用第一个纹理，并绑定纹理数据
    glBindTexture(GL_TEXTURE_2D, texture_id);


//4、设置渲染相关参数（矩形4个顶点、及其对应的纹理坐标）
    InitializeGeometry(program_id);

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
//6、取回数据到opencv，并显示结果

    show(mat.rows, mat.cols);

    return 0;
}