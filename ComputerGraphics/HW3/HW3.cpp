#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void triangle() {
	glBegin(GL_TRIANGLES);
	glVertex3d(0, 0, 0);
	glVertex3d(2, 0, 0);
	glVertex3d(1, 1.73, 0);
	glEnd();
}

void tetrahedron() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3d(1.0, 0.3, 0.3); // ÁÂ
	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glRotated(-120.0, 0.0, 0.1, 0.0);
	glRotated(-19.47, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glColor3d(0.4, 1.0, 0.4); // ¿ì
	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glRotated(-60.0, 0.0, 0.1, 0.0);
	glRotated(19.47, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glColor3d(0.5, 0.5, 1.0); // ÇÏ
	glPushMatrix();
	glTranslated(0.0, 0.0, 1.73);
	glRotated(-90, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glColor3d(0.7, 0.7, 0.7); //  Àü
	glPushMatrix();
	glTranslated(0.0, 0.0, 1.73);
	glRotated(-19.47, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glFlush();
}

void other3D() {
	
	glColor3d(0.5, 0.4, 0.1); // Wire Sphere
	glPushMatrix();
	glTranslated(1, 1.5, -2);
	glutWireSphere(1, 30, 30);
	glPopMatrix();

	glColor3d(1.0, 0.2, 0.6); // Wire Cone
	glPushMatrix();
	glTranslated(-1, 1, 1);
	glRotated(-60, 1.0, 0.2, 0.0);
	glutWireCone(1, 2, 30, 30);
	glPopMatrix();

	glColor3d(0.3, 0.7, 0.8); // Wire Torus
	glPushMatrix();
	glTranslated(0, -1, -2);
	glRotated(30, 0.3, 1.0, 0.0);
	glutWireTorus(0.5, 1, 20, 40);
	glPopMatrix();

	glFlush();
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tetrahedron();
	other3D();

	glFlush();
}

void init() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	gluLookAt(30.0, -20.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
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