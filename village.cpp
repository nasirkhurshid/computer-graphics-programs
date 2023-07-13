#include <iostream>
#include <GL/glut.h>
#include <math.h>

void myInit(void) {
    glClearColor(1, 1, 1, 0.0);
    glColor3f(0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glLineWidth(3.0);
    glPointSize(2);
}

class Point {
public:
    GLint x, y;
    Point(int a, int b) {
        x = a;
        y = b;
    }
};

int random(int x) {
    return rand() % x;
}

void transformation(float sx, float rx, float tx, float ry, float sy, float ty, int& p1, int& p2) {
    float matrix[3][3] = { {sx,rx,tx},
        {ry,sy,ty},
        {0,0,1} };
    int points[3][1] = { p1,p2,1 };
    float result[3][1] = {0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 1; ++j)
            for (int k = 0; k < 3; ++k)
                result[i][j] += matrix[i][k] * points[k][j];
    p1 = result[0][0];
    p2 = result[1][0];
}


void house(Point point, int width, int height) {
    glBegin(GL_LINE_LOOP);  //shell
    glVertex2i(point.x, point.y);
    glVertex2i(point.x + width / 2, point.y - (height / 3));
    glVertex2i(point.x + width / 2, point.y - height);
    glVertex2i(point.x - width / 2, point.y - height);
    glVertex2i(point.x - width / 2, point.y - (height / 3));
    glEnd();

    glBegin(GL_LINE_LOOP);  //door
    glVertex2i(point.x - width / 3, (point.y - height) + height / 3);
    glVertex2i(point.x - width / 8, (point.y - height) + height / 3);
    glVertex2i(point.x - width / 8, point.y - height);
    glVertex2i(point.x - width / 3, point.y - height);
    glEnd();

    glBegin(GL_LINE_LOOP);  //window
    glVertex2i(point.x - width / 7, point.y - (height / 3));
    glVertex2i(point.x + width / 6, point.y - (height / 3));
    glVertex2i(point.x + width / 6, point.y - (height / 2));
    glVertex2i(point.x - width / 7, point.y - (height / 2));
    glEnd();
    glBegin(GL_LINE_STRIP); //window glasses
    glVertex2i(((point.x - width / 7)+(point.x + width / 6))/2, point.y - (height / 3));
    glVertex2i(((point.x - width / 7) + (point.x + width / 6)) / 2, point.y - (height / 2));
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2i(point.x + width / 6, ((point.y - (height / 2)) + (point.y - (height / 3)))/2);
    glVertex2i(point.x - width / 7, ((point.y - (height / 2)) + (point.y - (height / 3)))/2);
    glEnd();

    glBegin(GL_LINE_STRIP);  //chimney
    glVertex2i(point.x - width / 2.5, point.y-height/3.5);
    glVertex2i(point.x - width / 2.5, point.y-height/12);
    glVertex2i(point.x - width / 3.5, point.y-height/12);
    glVertex2i(point.x - width / 3.5, point.y-height/5);
    glEnd();
}

void village() {
    glClear(GL_COLOR_BUFFER_BIT);
    house({ 70,120 }, 90, 90);
    house({ 180,120 }, 90, 90);
    house({ 290,120 }, 90, 90);
    house({ 400,120 }, 90, 90);

    house({ 100,450 }, 150, 150);
    house({ 290,450 }, 90, 90);
    house({ 400,450 }, 90, 90);
    house({ 350,150 }, 150, -150);
    glFlush();
}

int main()
{
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("Village");
    glutDisplayFunc(village);
    myInit();
    glutMainLoop();
}
