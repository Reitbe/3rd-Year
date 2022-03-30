// ����Ʈ�����а� 180008 ������

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>

int a = 80;  // Ÿ���� ����
int b = 50;  // Ÿ���� ����

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
	// 12�� ���⿡�� �ð�������� Ÿ���� �׸���.
	int disF1 = (4 * b * b + a * a * (1 - 4 * b)) / 4; // ��簡 �ϸ��� �κп����� �Ǻ���(Part A)
	int x = 0;
	int y = b;
	glColor3d(0.0, 1.0, 0.0);
	glVertex2i(x, y);
	while (b * b * x < a * a * y) { // �̺��� ���� ������ �Ǻ�
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
	// 3�� ���⿡�� �ݽð� �������� Ÿ���� �׸���.
	int disF2 = (4 * a * a + b * b * (1 - 4 * a)) / 4; // ��簡 ���� �κп����� �Ǻ���(part B)
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