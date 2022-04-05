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
vector<pair<int, int>> point;
int triangle_p1X;
int triangle_p1Y;
int triangle_p2X;
int triangle_p2Y;
int triangle_p3X;
int triangle_p3Y;
//--Ractangle--
int ractangle_p1X;   //Point One X 
int ractangle_p1Y;   //Point One Y
int ractangle_p2X;   //Point Two X
int ractangle_p2Y;   //Point Two Y
//--Circle--
int cocX;  //Centor of Circle X
int cocY;  //Centor of Circle Y
int Radius;

void plot8(int x, int y) {
	glColor3d(1.0, 0.0, 0.0);
	glVertex2i(cocX + x, cocY + y);
	glVertex2i(cocX - x, cocY + y);
	glVertex2i(cocX + x, cocY - y);
	glVertex2i(cocX - x, cocY - y);
	glVertex2i(cocX + y, cocY + x);
	glVertex2i(cocX - y, cocY + x);
	glVertex2i(cocX + y, cocY - x);
	glVertex2i(cocX - y, cocY - x);
}

void bresenham(int startX, int startY, int endX, int endY, string whatFigure) {
	int temp;
	if (startX > endX) { // lower X is startpoint
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
			if (whatFigure == "TRIANGLE_OUTLINE") { point.push_back(pair<int, int>(x, y)); glVertex2i(x, y); }
			else if(whatFigure == "CIRCLE_INLINE") plot8(x, y);
			else glVertex2i(x, y);
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
			if (whatFigure == "TRIANGLE_OUTLINE") { point.push_back(pair<int, int>(x, y)); glVertex2i(x, y); }
			else if (whatFigure == "CIRCLE_INLINE") plot8(x, y);
			else glVertex2i(x, y);
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
			if (whatFigure == "TRIANGLE_OUTLINE") { point.push_back(pair<int, int>(x, y)); glVertex2i(x, y); }
			else if (whatFigure == "CIRCLE_INLINE") plot8(x, y);
			else glVertex2i(x, y);
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
			if (whatFigure == "TRIANGLE_OUTLINE") { point.push_back(pair<int, int>(x, y)); glVertex2i(x, y); }
			else if (whatFigure == "CIRCLE_INLINE") plot8(x, y);
			else glVertex2i(x, y);
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
	glColor3d(0.0, 0.0, 1.0);

	int centorX = (int)((triangle_p1X + triangle_p2X + triangle_p3X) / 3);
	int centorY = (int)((triangle_p1Y + triangle_p2Y + triangle_p3Y) / 3);

	bresenham(centorX, centorY, triangle_p1X, triangle_p1Y, "");
	bresenham(centorX, centorY, triangle_p2X, triangle_p2Y, "");
	bresenham(centorX, centorY, triangle_p3X, triangle_p3Y, "");

	bresenham(triangle_p1X, triangle_p1Y, triangle_p2X, triangle_p2Y, "TRIANGLE_OUTLINE");
	for (int i = 0; i < point.size(); i++) { 	
		bresenham(centorX, centorY, point[i].first, point[i].second, "");
	}
	point.clear();

	bresenham(triangle_p2X, triangle_p2Y, triangle_p3X, triangle_p3Y, "TRIANGLE_OUTLINE");
	for (int i = 0; i < point.size(); i++) { 
		bresenham(centorX, centorY, point[i].first, point[i].second, "");
	}
	point.clear();

	bresenham(triangle_p1X, triangle_p1Y, triangle_p3X, triangle_p3Y, "TRIANGLE_OUTLINE");
	for (int i = 0; i < point.size(); i++) { 
		bresenham(centorX, centorY, point[i].first, point[i].second, "");
	}
	point.clear();
}

void circle() {
	glColor3d(1.0, 0.0, 0.0);

	int r = Radius;
	int x = r; // 3시 방향에서 시작함을 의미
	int y = 0;
	int F = 1 - r; // 반시계로 말아올리는 원의 판별식 초기값

	glVertex2i(cocX + x, cocY + y); // 점을 찍을 때는 원의 중심만큼 이동해준다.
	while (x > y) {
		bresenham(0, 0, x, y, "CIRCLE_INLINE");
		++y;
		if (F < 0) {
			F += 2 * y + 1;
		}
		else {
			--x;
			F += 2 * y - 2 * x + 1;
		}
	}
}


void ractangle() {
	glColor3d(0.0, 1.0, 0.0);

	int sx = (ractangle_p1X < ractangle_p2X) ? ractangle_p1X : ractangle_p2X; // s는 기울기가 양수인 대각선 아래쪽 점
	int sy = (ractangle_p1Y < ractangle_p2Y) ? ractangle_p1Y : ractangle_p2Y;
	int ex = (ractangle_p1X < ractangle_p2X) ? ractangle_p2X : ractangle_p1X; // e는 기울기가 양수인 대각선 위쪽 점
	int ey = (ractangle_p1Y < ractangle_p2Y) ? ractangle_p2Y : ractangle_p1Y;

	for (sx; sx <= ex; ++sx) {
		for (int y = sy; y <= ey; ++y) {
			glVertex2i(sx, y);
		}
	}
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

void playAll() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);

	circle();
	ractangle();
	triangle();

	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	vector<string> splitResult = split(readFile(), ':');
	//--Triangle--
	triangle_p1X = stoi(splitResult[2]);  //Point One X
	triangle_p1Y = stoi(splitResult[4]);  //Point One Y
	triangle_p2X = stoi(splitResult[6]);  //Point Two X
	triangle_p2Y = stoi(splitResult[8]);  //Point Two Y
	triangle_p3X = stoi(splitResult[10]);  //Point Three X
	triangle_p3Y = stoi(splitResult[12]);  //Point Three Y
	//--Ractangle--
	ractangle_p1X = stoi(splitResult[15]);   //Point One X 
	ractangle_p1Y = stoi(splitResult[17]);   //Point One Y
	ractangle_p2X = stoi(splitResult[19]);   //Point Two X
	ractangle_p2Y = stoi(splitResult[21]);   //Point Two Y
	//--Circle--
	cocX = stoi(splitResult[24]);  //Centor of Circle X
	cocY = stoi(splitResult[26]);  //Centor of Circle Y
	Radius = stoi(splitResult[28]); // Radius of Circle

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(301, 301);
	glutCreateWindow("HW1");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);

	glutDisplayFunc(playAll);

	glutMainLoop();

	return 0;
}