#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void quad() {
	glBegin(GL_QUADS);
	glRotated(0.1, 0.1, 0.1, 0.1);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);
	glVertex3d(1, 1, 0);
	glVertex3d(0, 1, 0);
	glEnd();
}

void cube() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 0.0, 0.0); // Red, ��
	glPushMatrix();
	quad();
	glPopMatrix();

	glColor3d(0.0, 1.0, 0.0); // Green, ��
	glPushMatrix();
	glRotated(-90.0, 0.0, 0.1, 0.0);
	quad();
	glPopMatrix();

	glColor3d(0.0, 0.0, 1.0); // Blue, ��
	glPushMatrix();
	glRotated(90.0, 1.0, 0.0, 0.0);
	quad();
	glPopMatrix();

	glColor3d(1.0, 1.0, 0.0); // Yellow, ��
	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glRotated(-90.0, 0.0, 0.1, 0.0);
	quad();
	glPopMatrix();

	glColor3d(1.0, 0.0, 1.0); // Magenta, ��
	glPushMatrix();
	glTranslated(0.0, 1.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	quad();
	glPopMatrix();

	glColor3d(0.0, 1.0, 1.0); // Cyan, ��
	glPushMatrix();
	glTranslated(0.0, 0.0, 1.0);
	quad();
	glPopMatrix();

	glFlush();
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube();
	glFlush();
	glutSwapBuffers();
}

void init() {
	glMatrixMode(GL_PROJECTION); // ������������ ��ȯ
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0); // �ش� ����ü �������� �׸��ڴ�.

	glMatrixMode(GL_MODELVIEW); // �ٽ� �𵨺�� ��ȯ
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // ī�޶�� A)�� ��ǥ����, B)�� ������ �ٶ󺻴�, C)Y�� ������ �Ӹ� ���� �����̴�.
	//gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(300, 300);
	glutCreateWindow("HW3");

	init();

	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}