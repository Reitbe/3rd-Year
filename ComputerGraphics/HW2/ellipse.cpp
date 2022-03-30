// 소프트웨어학과 180008 이준형

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>

int a = 80;  // 타원의 장축
int b = 50;  // 타원의 단축

void plot4(int x, int y) {
	glVertex2i(x, y);
	glVertex2i(-x, y);
	glVertex2i(x, -y);
	glVertex2i(-x, -y);
}

void ellipse() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	// part A
	// 12시 방향에서 시계방향으로 타원을 그린다.
	int disF1 = (4 * b * b + a * a * (1 - 4 * b)) / 4; // 경사가 완만한 부분에서의 판별식(Part A)
	int x = 0;
	int y = b;
	glColor3d(0.0, 1.0, 0.0);
	glVertex2i(x, y);
	while (b * b * x < a * a * y) { // 미분을 통한 기울기의 판별
		++x;
		if (disF1 < 0) {
			disF1 += b * b * (2 * x + 1);
		}
		else {
			--y;
			disF1 += b * b * (2 * x + 1) - 2 * a * a * y;
		}
		plot4(x, y);
	}
	
	// part B
	// 3시 방향에서 반시계 방향으로 타원을 그린다.
	int disF2 = (4 * a * a + b * b * (1 - 4 * a)) / 4; // 경사가 급한 부분에서의 판별식(part B)
	x = a;
	y = 0;
	glColor3d(1.0, 0.0, 0.0);
	glVertex2i(x, y);
	while (b * b * x > a * a * y) {
		++y;
		if (disF2 < 0) {
			disF2 += a * a * (2 * y + 1);
		}
		else {
			--x;
			disF2 += (-2) * b * b * x + a * a * (2 * y + 1);
		}
		plot4(x, y);
	}

	glEnd();
	glFlush();
}



int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(301, 301);
	glutCreateWindow("HW2");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);

	glutDisplayFunc(ellipse);
	glutMainLoop();

	return 0;
}