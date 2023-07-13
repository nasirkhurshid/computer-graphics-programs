#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <math.h>
#include <string>
using namespace std;

int screenHeight = 480;
int xmin = 150, xmax = 490, ymin = 150, ymax = 330;

struct Point {
	GLfloat x;
	GLfloat y;
	Point() {}
	Point(float a, float b) {
		x = a;
		y = b;
	}
};

Point p1, p2;

void drawLine(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
}

bool isOut(Point p) {
	if (p.x > xmax || p.x < xmin || p.y > ymax || p.y < ymin) {
		return true;
	}
	return false;
}

int outCode(Point p1, Point p2) {
	string code1, code2 = "";
	int c1, c2, res = 0, result = 0;
	int t1 = signbit(ymax - p1.y);
	int b1 = signbit(p1.y - ymin);
	int r1 = signbit(xmax - p1.x);
	int l1 = signbit(p1.x - xmin);
	code1 = to_string(t1) + to_string(b1) + to_string(r1) + to_string(l1);

	int t2 = signbit(ymax - p2.y);
	int b2 = signbit(p2.y - ymin);
	int r2 = signbit(xmax - p2.x);
	int l2 = signbit(p2.x - xmin);
	code2 = to_string(t2) + to_string(b2) + to_string(r2) + to_string(l2);

	if (code1 == code2 && code2 == "0000") {
		result = 1;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (code1[i] == '1' && code2[i] == '1') {
				res = 1;
				break;
			}
		}
		if (res == 1)
			result = 2;
		else {
			int r1 = 0, r2 = 0;
			for (int i = 0; i < 4; i++) {
				if (code1[i] == '1') {
					r1++;
				}
				if (code2[i] == '1') {
					r2++;
				}
			}
			if (r1 > 0 || r2 > 0)
				result = 3;
			if (r1 > 0 && r2 > 0)
				result = 4;
		}
	}
	return result;
}

int toClip(Point& p1, Point& p2, Point& tp1, Point& tp2) {
	float m = 0.0;
	if (outCode(p1, p2) == 3 && isOut(p1)) {
		tp1.x = p1.x;
		tp1.y = p1.y;
	}
	if (outCode(p1, p2) == 3 && isOut(p2)) {
		tp1.x = p2.x;
		tp1.y = p2.y;
	}
	if (outCode(p1, p2) == 4) {
		tp1.x = p1.x;
		tp1.y = p1.y;
		tp2.x = p2.x;
		tp2.y = p2.y;
	}
	do {
		int code = outCode(p1, p2);
		m = (p2.y - p1.y) / (p2.x - p1.x);
		if (code == 1) {
			return 1;
		}
		if (code == 2) {
			return 0;
		}
		if (isOut(p1)) {
			if (signbit(p1.x - xmin)) {	//left
				p1.y = p1.y + m * (xmin - p1.x);
				p1.x = xmin;
			}
			if (signbit(xmax - p1.x)) {	//right
				p1.y = p1.y + m * (xmax - p1.x);
				p1.x = xmax;
			}
			if (signbit(p1.y - ymin)) {	//bottom
				p1.x = p1.x + (ymin - p1.y) / m;
				p1.y = ymin;
			}
			if (signbit(ymax - p1.y)) {	//top
				p1.x = p1.x + (ymax - p1.y) / m;
				p1.y = ymax;
			}
		}
		if (isOut(p2)) {
			if (signbit(p2.x - xmin)) {	//left
				p2.y = p2.y + m * (xmin - p2.x);
				p2.x = xmin;
			}
			if (signbit(xmax - p2.x)) {	//right
				p2.y = p2.y + m * (xmax - p2.x);
				p2.x = xmax;
			}
			if (signbit(p2.y - ymin)) {	//bottom
				p2.x = p2.x + (ymin - p2.y) / m;
				p2.y = ymin;
			}
			if (signbit(ymax - p2.y)) {	//top
				p2.x = p2.x + (ymax - p2.y) / m;
				p2.y = ymax;
			}
		}
	} while (1);
	return 0;
}

void clip(Point p1, Point p2) {
	Point tp1(0, 0), tp2(0, 0);
	int res = isOut(p1);
	int result = toClip(p1, p2, tp1, tp2);
	glBegin(GL_LINES);
	glColor3f(0, 1.0, 0);
	if (toClip(p1, p2, tp1, tp2) == 1) {
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		if (tp1.x != 0 && tp2.x == 0) {
			glColor3f(1.0, 0, 0);
			glVertex2f(tp1.x, tp1.y);
			if (res == 0) {
				glVertex2f(p2.x, p2.y);
			}
			else {
				glVertex2f(p1.x, p1.y);
			}
		}
		else {
			if (tp1.x != 0 && tp2.x != 0) {
				glColor3f(1.0, 0, 0);
				glVertex2f(tp1.x, tp1.y);
				glVertex2f(p1.x, p1.y);
				glVertex2f(tp2.x, tp2.y);
				glVertex2f(p2.x, p2.y);
			}
		}
	}
	else {
		glColor3f(1.0, 0, 0);
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
	}
	glEnd();
	glFlush();
}

void myMouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p1.x = x;
		p1.y = screenHeight - y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		p2.x = x;
		p2.y = screenHeight - y;
		clip(p1, p2);
	}
}

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(4.0);
	glLineWidth(4.0);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2i(150, 150);
	glVertex2i(150, 330);
	glVertex2i(490, 330);
	glVertex2i(490, 150);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Clipping");
	glutDisplayFunc(display);
	glutMouseFunc(myMouseFunc);
	init();
	glutMainLoop();
	return 0;
}