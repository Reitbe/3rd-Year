#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>





void bresenham() { //���Ⱑ 0<m<1�� �� �۵��Ѵ�.
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
	int F = 2 * H - W; // F�� �ʱⰪ. ������ �������� ���� �ľ�
	int disF1 = 2 * H; // �ߴ������� ������ �Ʒ��ִ�. y����
	int disF2 = 2 * (H - W); // �ߴ������� ������ �����ִ�. y+1

	for (x; x <= endX; ++x) {
		glVertex2i(x, y); // ������ ���
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