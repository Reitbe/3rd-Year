#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>

int startX = 10;
int startY = 80;
int endX = 30;
int endY = 10;

void discrimination(int n, int x, int y) {
	switch (n)
	{
	case 1:
		glVertex2i(x, y);
		break;
	case 2:
		glVertex2i(x - 2 * (x - startX), y);
		break;
	case 3:
		glVertex2i(x, y - 2 * (y - startY));
		break;
	case 4:
		glVertex2i(x, y);
		break;
	}
}
void bresenham() { //기울기가 0<m<1일 때 작동한다.
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	int temp = 0;
	int caseNumber;

	/*
	if (startX < startX && startY < endY) { caseNumber = 1; } // 1
	else if (startX > startX && startY < endY) { endX = endX + 2 * (startX - endX); caseNumber = 2; } // 3
	else if (startX < startX && startY > endY) { endY = endY + 2 * (startY - endY); caseNumber = 3;} // 2
	else {
		temp = startX; startX = endX; endX = temp;
		temp = startY; startY = endY; endY = temp;
		caseNumber = 4;
	} //4
	*/
	int x = startX;
	int y = startY;
	int W = endX - startX;
	int H = endY - startY;
	int F;

	if (H < 0) temp = 1;

	if (W >= H && temp == 0) { // 기울기가 0<m<1인 경우, 동시에 우상향
		F = 2 * H - W; 
		while (x <= endX) {
			glVertex2i(x, y);
			//discrimination(caseNumber, x, y); // 시작점 찍고
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
	else if(W < H && temp == 0){ // 기울기가 1<m<무한인 경우
		F = 2 * W - H;
		while (y <= endY) {
			glVertex2i(x, y);
			//discrimination(caseNumber, x, y);
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
	else if (W > -H && temp == 1) {
		F = 2 * H + W;
		while (x <= endX) {
			glVertex2i(x, y);
			//discrimination(caseNumber, x, y); // 시작점 찍고
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
	else if (W < -H && temp == 1) {
		F = 2 * W + H;
		while (y >= endY) {
			glVertex2i(x, y);
			//discrimination(caseNumber, x, y); // 시작점 찍고
			if (F < 0) {
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