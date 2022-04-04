#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> point;
int p1X=-70;
int p1Y=30;
int p2X=50;
int p2Y=40;
int p3X=80;
int p3Y=60;


void bresenham(int startX, int startY, int endX, int endY, int isOutside) {
	//discrimination(startX, startY, endX, endY);
	int temp;
	if (startX > endX) {
		temp = startX; startX = endX; endX = temp;
		temp = startY; startY = endY; endY = temp;
	}

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
			if(isOutside == 1) point.push_back(pair<int, int>(x, y));
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
	else if (W < H && isDownside == false) { // 1 < m < infinite
		F = 2 * W - H;
		while (y <= endY) {
			if (isOutside == 1) point.push_back(pair<int, int>(x, y));
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
			if (isOutside == 1) point.push_back(pair<int, int>(x, y));
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
	else { // -infinite < m < -1
		F = 2 * W + H;
		while (y >= endY) {
			if (isOutside == 1) point.push_back(pair<int, int>(x, y));
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


}

void triangle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	int centorX = (int)((p1X + p2X + p3X) / 3);
	int centorY = (int)((p1Y + p2Y + p3Y) / 3);

	bresenham(centorX, centorY, p1X, p1Y, 0);
	bresenham(centorX, centorY, p2X, p2Y, 0);
	bresenham(centorX, centorY, p3X, p3Y, 0);

	bresenham(p1X, p1Y, p2X, p2Y, 1);
	for (int i = 0; i < point.size(); i++) { // RED
		glColor3d(1.0, 0.0, 0.0);
		bresenham(centorX, centorY, point[i].first, point[i].second, 0);
	}
	point.clear();
	
	bresenham(p2X, p2Y, p3X, p3Y, 1);
	for (int i = 0; i < point.size(); i++) { // GREEN
		glColor3d(0.0, 1.0, 0.0);
		bresenham(centorX, centorY, point[i].first, point[i].second, 0);
	}
	point.clear();
	
	bresenham(p1X, p1Y, p3X, p3Y, 1);
	for (int i = 0; i < point.size(); i++) { // BLUE
		glColor3d(0.0, 0.0, 1.0);
		bresenham(centorX, centorY, point[i].first, point[i].second, 0);
	}
	point.clear();

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

	glutDisplayFunc(triangle);
	glutMainLoop();

	return 0;
}