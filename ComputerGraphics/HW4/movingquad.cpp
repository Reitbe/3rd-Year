#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void quad() {
	glBegin(GL_QUADS);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(0, 1, 0);
	glEnd();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(0.0, 1.0, 0.0);
	glRotated(0.2, 1.0, 1.0, 1.1);
	quad();
	glutSwapBuffers();
}

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION); // ������������ ��ȯ
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0); // �ش� ����ü �������� �׸��ڴ�.

	glMatrixMode(GL_MODELVIEW);// �ٽ� �𵨺�� ��ȯ
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);// ī�޶�� A)�� ��ǥ����, B)�� ������ �ٶ󺻴�, C)Y�� ������ �Ӹ� ���� �����̴�.

	glEnable(GL_DEPTH_TEST);
}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("HW3");

	init();

	glutDisplayFunc(display);
	glutTimerFunc(1, Timer, 1);
	glutMainLoop();

	return 0;
}