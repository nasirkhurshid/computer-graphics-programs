#include <iostream>
#include <GL/glut.h>
#include <math.h>

GLint w = 400, h = 400;

void myInit(void) {
    glClearColor(.839, .611, .349, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glLineWidth(3.0);
    glPointSize(2);
}

void chess() {
    glClear(GL_COLOR_BUFFER_BIT);
    int x, y = 0;
    for (int i = 0; i < 8; i++) {
        x = 50;
        y += 50;
        for (int j = 0; j < 8; j++) {
            glColor3f(.435, .262, .164);
            //if ((i % 2 == 0 && j % 2 == 0)|| (i % 2 == 1 && j % 2 == 1))
            if((i+j)%2==0)
                glColor3f(.8, .7, .5);
            glRecti(x, y, x + 50, y + 50);
            x += 50;
        }
    }
    glFlush();
}

int main()
{
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Program");
    glutDisplayFunc(chess);
    myInit();
    glutMainLoop();
}
