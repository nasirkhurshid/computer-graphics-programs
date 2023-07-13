#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <fstream>
using namespace std;

int x1 = 100, x2 = 540, yy = 100, y2 = 380;
struct Point {
	GLdouble x;
	GLdouble y;
	Point() {
		x = y = 0;
	}
	Point(const Point& p) {
		x = p.x;
		y = p.y;
	}
} p1, p2;

struct code {
	int t, b, r, l;
	code() {
		t = b = r = l = 0;
	}
	code getcode(Point p) {
		t = b = r = l = 0;
		if (p.x < x1)
			r = 1;
		if (p.x > x2)
			l = 1;
		if (p.y < yy)
			b = 1;
		if (p.y > y2)
			t = 1;
		return *this;
	}
	bool inside(code cd) {
		if (!cd.t && !t && !cd.b && !b && !cd.r && !r && !cd.l && !l)
			return 1;
		return 0;
	}
	bool todraw(code cd) {
		if (cd.t && t || cd.b && b || cd.r && r || cd.l && l)
			return 0;
		return 1;
	}
};

bool out(Point p) {
	if (p.x > x2 || p.x < x1 || p.y > y2 || p.y < yy)
		return 1;
	return 0;

}

void draw(Point p1, Point p2) {
	glBegin(GL_LINES);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glEnd();
}

int cohensutherland(Point &p1, Point &p2, Point &tp1, Point& tp2) {
	code code1, code2;
	double m = 0.0;
	do {
		code1 = code1.getcode(p1);
		code2 = code2.getcode(p2);
		m = (p2.y - p1.y);
		m /= (p2.x - p1.x);
		if (code1.inside(code2)) {
			return 1;
		}
		if ((out(p1) && out(p2))&&!code1.todraw(code2)) {
			return 0;
		}
		if (out(p1)) {
			if (p1.x < x1) {
				p1.y = p1.y + m * (x1 - p1.x);
				p1.x = x1;
			}
			if (x2 < p1.x) {
				p1.y = p1.y + m * (x2 - p1.x);
				p1.x = x2;
			}
			if (p1.y < yy) {
				p1.x = p1.x + (yy - p1.y) / m;
				p1.y = yy;
			}
			if (y2 < p1.y) {
				p1.x = p1.x + (y2 - p1.y) / m;
				p1.y = y2;
			}
		}
		if (out(p2)) {
			if (p2.x< x1) {
				p2.y = p2.y + m * (x1 - p2.x);
				p2.x = x1;
			}
			if (x2 < p2.x) {
				p2.y = p2.y + m * (x2 - p2.x);
				p2.x = x2;
			}
			if (p2.y < yy) {
				p2.x = p2.x + (yy - p2.y) / m;
				p2.y = yy;
			}
			if (y2 < p2.y) {
				p2.x = p2.x + (y2 - p2.y) / m;
				p2.y = y2;
			}
		}
	} while (1);
	return 0;
}


void clipping(Point p1, Point p2) {
	Point p11(p1), p22(p2);
	cohensutherland(p1, p2, p11, p22);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2d(p11.x, p11.y);
	glVertex2d(p1.x, p1.y);
	glColor3f(0, 1, 0);
	glVertex2d(p1.x, p1.y);
	glVertex2d(p2.x, p2.y);
	glColor3f(1, 0, 0);
	glVertex2d(p2.x, p2.y);
	glVertex2d(p22.x, p22.y);
	glEnd();
}

void mouseFunc(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p1.x = x;
		p1.y = 480 - y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		p2.x = x;
		p2.y = 480 - y;
		if (p1.x > x1 && p2.x > x1 && p1.x<x2 && p2.x<x2 && p1.y>yy && p2.y>yy && p1.y < y2 && p2.y < y2) {
			glColor3f(0, 1, 0);
			draw(p1, p2);

		}
		else if (p1.x < x1 && p2.x < x1 || p1.x>x2 && p2.x>x2 || p1.y<yy && p2.y<yy || p1.y > y2 && p2.y > y2) {
			glColor3f(1, 0, 0);
			draw(p1, p2);
		}
		else {
			clipping(p1, p2);
		}
		glFlush();
	}
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	glVertex2i(100, 100);
	glVertex2i(100, 380);
	glVertex2i(540, 380);
	glVertex2i(540, 100);
	glVertex2i(100, 100);
	glEnd();
	glFlush();
}

void myInit() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(3.0);
	gluOrtho2D(0, 640, 0, 480);
}


int main(int argc, char** argv) {
	glutInitWindowSize(640, 480);
	glutCreateWindow("Program");
	glutDisplayFunc(display);
	glutMouseFunc(mouseFunc);
	myInit();
	glutMainLoop();
}