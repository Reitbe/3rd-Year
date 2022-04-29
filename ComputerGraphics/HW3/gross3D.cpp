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

void cube() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 0.0, 0.0); // Red, 후
	glPushMatrix();
	quad();
	glPopMatrix();

	glColor3d(0.0, 1.0, 0.0); // Green, 좌
	glPushMatrix();
	glRotated(-90.0, 0.0, 0.1, 0.0);
	quad();
	glPopMatrix();

	glColor3d(0.0, 0.0, 1.0); // Blue, 하
	glPushMatrix();
	glRotated(90.0, 1.0, 0.0, 0.0);
	quad();
	glPopMatrix();

	glColor3d(1.0, 1.0, 0.0); // Yellow, 우
	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glRotated(-90.0, 0.0, 0.1, 0.0);
	quad();
	glPopMatrix();

	glColor3d(1.0, 0.0, 1.0); // Magenta, 상
	glPushMatrix();
	glTranslated(0.0, 1.0, 0.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	quad();
	glPopMatrix();

	glColor3d(0.0, 1.0, 1.0); // Cyan, 전
	glPushMatrix();
	glTranslated(0.0, 0.0, 1.0);
	quad();
	glPopMatrix();

	glFlush();
}

void other3D() {
	
	glColor3d(1.0, 1.0, 0.0); // Wire Sphere
	glPushMatrix();
	glTranslated(1, 1.5, -2);
	glutWireSphere(1, 30, 30);
	glPopMatrix();

	glColor3d(0.0, 1.0, 1.0); // Wire Cone
	glPushMatrix();
	glTranslated(-1, 1, 1);
	glutWireCone(1, 2, 30, 30);
	glPopMatrix();

	glColor3d(1.0, 0.0, 1.0); // Wire Torus
	glPushMatrix();
	glTranslated(0, -1, -2);
	glutWireTorus(0.5, 1, 20, 40);
	glPopMatrix();

	glFlush();
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cube();
	other3D();

	glFlush();
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
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