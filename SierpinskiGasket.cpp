#include <iostream>
#include <GL/glut.h>

class Point {
public:
    GLint x, y;
};

int random(int n) {
    return rand() % n;
}

void myInit(void) {
    //glClearColor(.3, .2, .1, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 320, 0, 320);
    glLineWidth(3.0);
    glPointSize(5);
    //glColor3f(1.0, 1.0, 0);
}

void drawDot(GLint x, GLint y) {
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void Sierpinski() {
    Point T[3] = { {10,10},{300,10},{150,300} };
    int index = random(3);
    Point point = T[index];
    glClear(GL_COLOR_BUFFER_BIT);
    drawDot(point.x, point.y);
    for (int i = 0; i < 500000; i++) {
        index = random(3);
        point.x = (point.x + T[index].x) / 2;
        point.y = (point.y + T[index].y) / 2;
        drawDot(point.x, point.y);
    }
    glFlush();
}


int main()
{
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Program");
    glutDisplayFunc(Sierpinski);
    myInit();
    glutMainLoop();
}
