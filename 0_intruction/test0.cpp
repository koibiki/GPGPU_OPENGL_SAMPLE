//
// Created by chengli on 18-5-17.
//
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>

GLuint v, f, p;
float lpos[4] = {1, 0.5, 1, 0};

void changeSize(int w, int h) {
    //
    if (h == 0) {
        h = 1;
    }
    float ratio = 1.0f * w / h;
    //
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, w, h);

    gluPerspective(45, ratio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
}

float a = 0;

void renderScene() {
    //clear scene every draw
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // init matrix
    glLoadIdentity();
    //locate camera
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, -1.0, 0.0f, 1.0f, 0.0f);

    glLightfv(GL_LIGHT0, GL_POSITION, lpos);
    //create rotation matrix   a is the
    glRotatef(a, 0, 1, 1);
    glutSolidTeapot(1);
    a += 0.1;
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("GPGPU Tutorial");

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);

    glutReshapeFunc(changeSize);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glutMainLoop();

    return 0;
}

