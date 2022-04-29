#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 1.0, 0.0);
	glPushMatrix();
	glTranslated(1, 1, 0);
	glutSolidSphere(1, 30, 30);
	glPopMatrix();

	glColor3d(0.0, 1.0, 1.0);
	glPushMatrix();
	glTranslated(-1, 1, 0);
	glutWireCone(1, 2, 30, 30);
	glPopMatrix();

	glColor3d(1.0, 0.0, 1.0);
	glPushMatrix();
	glTranslated(0, -1, 0);
	glutWireTorus(1, 2, 20, 40);
	glPopMatrix();

	glFlush();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION); // ������������ ��ȯ
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0); // �ش� ����ü �������� �׸��ڴ�.

	glMatrixMode(GL_MODELVIEW);// �ٽ� �𵨺�� ��ȯ
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);// ī�޶�� A)�� ��ǥ����, B)�� ������ �ٶ󺻴�, C)Y�� ������ �Ӹ� ���� �����̴�.

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("HW3");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}