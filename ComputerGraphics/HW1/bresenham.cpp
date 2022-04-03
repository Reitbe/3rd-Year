#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>

int startX = 80;
int startY = 50;
int endX = 10;
int endY = 80;

void discrimination() { // startX is always smaller than endX
	int temp;
	if (startX > endX) {
		temp = startX; startX = endX; endX = temp;
		temp = startY; startY = endY; endY = temp;
	}
}

void bresenham() { 
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	discrimination();

	bool isDownside = false; // Line go to downside?
	int x = startX;
	int y = startY;
	int W = endX - startX;
	int H = endY - startY;
	int F;

	if (H < 0) isDownside = 1;

	if (W >= H && isDownside == false) { // 0 < m < 1
		F = 2 * H - W; 
		while (x <= endX) {
			glVertex2i(x, y);
			if (F < 0) {
				F += 2 * H;
			}
			else {
				++y;
				F += 2 * (H - W);
			}
			++x;
		}
	}
	else if(W < H && isDownside == false){ // 1 < m < infinite
		F = 2 * W - H;
		while (y <= endY) {
			glVertex2i(x, y);
			if (F < 0) {
				F += 2 * W;
			}
			else {
				++x;
				F += 2 * (W - H);
			}
			++y;
		}
	}
	else if (W > -H && isDownside == true) { // -1 < m < 0
		F = 2 * H + W;
		while (x <= endX) {
			glVertex2i(x, y);
			if (F < 0) {
				--y;
				F += 2 * (H + W);
			}
			else {
				F += 2 * H;
			}
			++x;
		}
	}
	else{ // -infinite < m < -1
		F = 2 * W + H;
		while (y >= endY) {
			glVertex2i(x, y);
			if (F > 0) {
				++x;
				F += 2 * (H + W);
			}
			else {
				F += 2 * W;
			}
			--y;
		}
	}

	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(301, 301);
	glutCreateWindow("HW1");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);

	glutDisplayFunc(bresenham);
	glutMainLoop();

	return 0;
}