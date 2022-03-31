#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>

int cocX = 1;  //Centor of Circle X
int cocY = 1;  //Centor of Circle Y
int Radius = 50;

void plot8(int x, int y) {
	glColor3d(1.0, 0.0, 0.0);
	glVertex2i(cocX +x, cocY +y);
	glVertex2i(cocX -x, cocY +y);
	glVertex2i(cocX +x, cocY -y);
	glVertex2i(cocX -x, cocY -y);
	glVertex2i(cocX +y, cocY +x);
	glVertex2i(cocX -y, cocY +x);
	glVertex2i(cocX +y, cocY -x);
	glVertex2i(cocX -y, cocY -x);
}

void bresenhamLine(int endX, int endY) { 
	int x = 0; // ������ �������� (0,0)���� �ǹ�
	int y = 0;
	int W = endX; // ���� endX - startX ����, start������ �����̹Ƿ� ������ ǥ���ߴ�.
	int H = endY;

	int F = 2 * H - W; // F�� �ʱⰪ. ������ �������� ���� �ľ�
	int disF1 = 2 * H; // �ߴ������� ������ �Ʒ��ִ�. y����
	int disF2 = 2 * (H - W); // �ߴ������� ������ �����ִ�. y+1
	
	for (x; x <= endX; ++x) {
		plot8(x,y); 
		if (F < 0) {
			F += disF1;
		}
		else {
			++y;
			F += disF2;
		}
	}
}

void circle() {  
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	
	int r = Radius;
	int x = r; // 3�� ���⿡�� �������� �ǹ�
	int y = 0;
	int F = 1 - r; // �ݽð�� ���ƿø��� ���� �Ǻ��� �ʱⰪ

	glColor3d(1.0, 0.0, 0.0);
	glVertex2i(cocX+x, cocY+y); // ���� ���� ���� ���� �߽ɸ�ŭ �̵����ش�.
	while (x > y) { 
		bresenhamLine(x, y);
		++y;
		if (F < 0) {
			F += 2 * y + 1;
		}
		else {
			--x;
			F += 2 * y - 2 * x + 1;
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

	glutDisplayFunc(circle);
	glutMainLoop();

	return 0;
}