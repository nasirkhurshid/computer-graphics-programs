#include <iostream>
#include <GL/glut.h>
#include <math.h>

GLint width = 640, height = 480;
GLdouble A, B, C, D;
void myInit(void) {
    //glClearColor(.3, .2, .1, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, 0, height);
    glLineWidth(3.0);
    glPointSize(2); 
    //glColor3f(1.0, 1.0, 0);
    A = width / 4;
    B = 0;
    C = D = height / 2;
}

void plot() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (GLdouble x = 0.0; x < 4.0; x += 0.005) {
        GLdouble funct = exp(-x) * cos(2 * 3.141592965 * x);
        glVertex2d(A * x + B, C * funct + D);
    }
    glEnd();
    glFlush();
}

void plot2() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (GLdouble x = 0.0; x < 300.0; x += 3) {
        GLdouble funct = 300 - 100 * cos((2 * 3.1415 * x) / 100) + 30 * cos((4 * 3.1415 * x) / 100) + 6 * cos((6 * 3.1415 * x) / 100);
        glVertex2d(x + 100, funct + 100);
    }
    glEnd();
    glFlush();
}

int main()
{
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Program");
    glutDisplayFunc(plot2);
    myInit();
    glutMainLoop();
}
