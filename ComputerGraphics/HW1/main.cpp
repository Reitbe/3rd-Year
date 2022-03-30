#include <GL/glew.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//--Triangle--
int cotX;  //Centor of Triangle X
int cotY;  //Centor of Triangle Y
int tH;    //Triangle Height
int tBW;   //Triangle Basewidth
//--Ractangle--
int p1X;   //Point One X 
int p1Y;   //Point One Y
int p2X;   //Point Two X
int p2Y;   //Point Two Y
//--Circle--
int cocX;  //Centor of Circle X
int cocY;  //Centor of Circle Y
int Radius;

//--bresenham--
int startX;
int startY;
int endX;
int endY;


void bresenham() { //기울기가 0<m<1일 때 작동한다.
	int x = startX;
	int y = startY;
	int W = endX - startX;
	int H = endY - startY;
	int F = 2 * H - W; 
	int disF1 = 2 * H;
	int disF2 = 2 * (H - W); 
	for (x; x <= endX; ++x) {
		glVertex2i(x, y); 
		if (F < 0) {
			F += disF1;
		}
		else {
			++y;
			F += disF2;
		}
	}
}

/*
void triangle() { 
	
	startX = cotX - 0.5 * tBW;
	startY = cotY - 0.33 * tH; 
	endX = cotX;
	endY = cotY + 0.66 * tH;  
	
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	int x;
	int y=sy;

	for (x=sx; x <= ex; ++x) {
		for (int ty = y; ty >= y; --ty) {
			bresenham();
		}
	}
	glEnd();
	glFlush();

}
*/

void oneEightCircle(int x, int y) {
	int r = Radius;
	startX = x;
	startY = y;
	double angle;

	for (angle = 0.25 * 3.14; angle <= 0.5 * 3.14; angle += 0.01) {
		endX = startX + r * sin(angle);
		endY = startY + r * cos(angle);
		bresenham();
	}

}

void circle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3d(1.0, 0.0, 0.0);

	oneEightCircle(cocX, cocY);
	oneEightCircle(cocX, -cocY);
	oneEightCircle(-cocX, cocY);
	oneEightCircle(-cocX, -cocY);
	oneEightCircle(cocY, cocX);
	oneEightCircle(cocY, -cocX);
	oneEightCircle(-cocY, cocX);
	oneEightCircle(-cocY, -cocX);

	glEnd();
	glFlush();
}

void ractangle() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glColor3d(0.0, 1.0, 0.0);
	int sx = (p1X < p2X) ? p1X : p2X; // s는 기울기가 양수인 대각선 아래쪽
	int sy = (p1Y < p2Y) ? p1Y : p2Y;
	int ex = (p1X < p2X) ? p2X : p1X; // e는 기울기가 양수인 대각선 위쪽
	int ey = p2Y; (p1Y < p2Y) ? p2Y : p1Y;

	for (sx; sx <= ex; ++sx) {
		for (int y = sy; y <= ey; ++y) {
			glVertex2i(sx, y);
		}
	}
	glEnd();
	glFlush();
}

vector<string> split(vector<string> rawData, char Delimiter) { // 구분자를 기준으로 string split
	vector<string> result;
	string buffer;                     
	string line;
	for (int i = 0; i < rawData.size(); i++) {
		line = rawData[i];
		istringstream iss(line);             
		while (getline(iss, buffer, Delimiter)) {
			result.push_back(buffer);           
		}
	}
	return result;
}

vector<string> readFile() { // 파일을 한 줄씩 읽어서 rawData vector에 저장.
	vector<string> rawData;
	string line;
	ifstream file("dataFile.txt");
	if (file.is_open()) {
		while (getline(file, line)) {
			rawData.push_back(line);
		}
	}
	return rawData;
}

int main(int argc, char** argv)
{
	vector<string> splitResult = split(readFile(), ':');
	//--Triangle--
	cotX = stoi(splitResult[2]);  //Centor of Triangle X
	cotY = stoi(splitResult[4]);  //Centor of Triangle Y
	tH = stoi(splitResult[6]);    //Triangle Height
	tBW = stoi(splitResult[8]);   //Triangle Basewidth
	//--Ractangle--
	p1X = stoi(splitResult[11]);   //Point One X 
	p1Y = stoi(splitResult[13]);   //Point One Y
	p2X = stoi(splitResult[15]);   //Point Two X
	p2Y = stoi(splitResult[17]);   //Point Two Y
	//--Circle--
	cocX = stoi(splitResult[20]);  //Centor of Circle X
	cocY = stoi(splitResult[22]);  //Centor of Circle Y
	Radius = stoi(splitResult[24]);


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
	glutDisplayFunc(ractangle);
	//glutDisplayFunc(triangle);

	glutMainLoop();

	return 0;
}