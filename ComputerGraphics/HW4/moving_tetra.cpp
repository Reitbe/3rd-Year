#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void triangle() {
	glBegin(GL_TRIANGLES);
	glColor3d(1.0, 1.0, 0.0); 
	glVertex3d(0, 0, 0);
	glColor3d(0.0, 1.0, 1.0); 
	glVertex3d(2, 0, 0);
	glColor3d(1.0, 0.0, 1.0); 
	glVertex3d(1, 1.73, 0);
	glEnd();
}

void tetrahedron() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glRotated(-120.0, 0.0, 0.1, 0.0);
	glRotated(-19.47, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, 0.0, 0.0);
	glRotated(-60.0, 0.0, 0.1, 0.0);
	glRotated(19.47, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, 1.73);
	glRotated(-90, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.0, 0.0, 1.73);
	glRotated(-19.47, 0.1, 0.0, 0.0);
	triangle();
	glPopMatrix();
}

void display() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glRotated(0.5, 0.0, 1.0, 0.0);
	glRotated(0.3, 1.0, 0.0, 0.0);
	tetrahedron();

	glutSwapBuffers();
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