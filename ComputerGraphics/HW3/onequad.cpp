#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void quad() {
	glBegin(GL_QUADS);

	glColor3d(1.0, 0.0, 0.0);
	glVertex3d(0, 0, 0);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3d(1, 0, 0);
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(1, 1, 0);
	glColor3d(0.0, 0.0, 1.0);
	glVertex3d(0, 1, 0);
	glEnd();
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	quad();

	glFlush();
}

void init() {
	glMatrixMode(GL_PROJECTION); // ������������ ��ȯ
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0); // �ش� ����ü �������� �׸��ڴ�.

	glMatrixMode(GL_MODELVIEW);// �ٽ� �𵨺�� ��ȯ
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 30.0,    0.0, 0.0, 0.0,    0.0, 1.0, 0.0);// ī�޶�� A)�� ��ǥ����, B)�� ������ �ٶ󺻴�, C)Y�� ������ �Ӹ� ���� �����̴�.

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