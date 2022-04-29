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
	glMatrixMode(GL_PROJECTION); // 프로젝션으로 전환
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0); // 해당 절두체 범위에서 그리겠다.

	glMatrixMode(GL_MODELVIEW);// 다시 모델뷰로 전환
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);// 카메라는 A)저 좌표에서, B)저 지점을 바라본다, C)Y축 방향이 머리 위쪽 방향이다.

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