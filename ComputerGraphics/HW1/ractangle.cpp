#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int p1X = 10;   //Point One X 
int p1Y = 10;   //Point One Y
int p2X = 100;   //Point Two X
int p2Y = 100;   //Point Two Y


void ractangle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3d(0.0, 1.0, 0.0);
	int sx = (p1X < p2X) ? p1X : p2X; // s는 기울기가 양수인 대각선 아래쪽
	int sy = (p1Y < p2Y) ? p1Y : p2Y;
	int ex = (p1X < p2X) ? p2X : p1X; // e는 기울기가 양수인 대각선 위쪽
	int ey = p2Y; (p1Y < p2Y) ? p2Y : p1Y;

	for (sx; sx <= ex; ++sx) {
		for (int y=sy; y <= ey; ++y) {
			glVertex2i(sx, y);
		}
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(301, 301);
	glutCreateWindow("HW1");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);

	glutDisplayFunc(ractangle);
	glutMainLoop();

	return 0;
}