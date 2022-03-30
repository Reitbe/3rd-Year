#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>





void bresenham() { //기울기가 0<m<1일 때 작동한다.
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	int startX = 10;
	int startY = 10;
	int endX = 80;
	int endY = 20;
	int W = endX - startX;
	int H = endY - startY;
	int x = startX;
	int y = startY;
	int F = 2 * H - W; // F의 초기값. 중점과 직선과의 관계 파악
	int disF1 = 2 * H; // 중단점보다 직선이 아래있다. y유지
	int disF2 = 2 * (H - W); // 중단점보다 직선이 위에있다. y+1

	for (x; x <= endX; ++x) {
		glVertex2i(x, y); // 시작점 찍고
		if (F < 0) {
			F += disF1;
		}
		else {
			++y;
			F += disF2;
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

	glutDisplayFunc(bresenham);
	glutMainLoop();

	return 0;
}