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
	int x = 0; // 직선의 시작점이 (0,0)임을 의미
	int y = 0;
	int W = endX; // 본래 endX - startX 지만, start지점이 원점이므로 끝점만 표시했다.
	int H = endY;

	int F = 2 * H - W; // F의 초기값. 중점과 직선과의 관계 파악
	int disF1 = 2 * H; // 중단점보다 직선이 아래있다. y유지
	int disF2 = 2 * (H - W); // 중단점보다 직선이 위에있다. y+1
	
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
	int x = r; // 3시 방향에서 시작함을 의미
	int y = 0;
	int F = 1 - r; // 반시계로 말아올리는 원의 판별식 초기값

	glColor3d(1.0, 0.0, 0.0);
	glVertex2i(cocX+x, cocY+y); // 점을 찍을 때는 원의 중심만큼 이동해준다.
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