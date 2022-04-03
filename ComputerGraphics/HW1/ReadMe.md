# HW1

강의시간에 설명한 바와 같이 OpenGL 이 사용 가능한 Visual Studio 를 통해 C/C++ program을 작성하여 삼각형, 사각형, 원 등 서너개의 다각형을 그리되 각 pixel 마다 해당 pixel이 속한 다각형을 찾아 그 다각형의 색깔을 pixel에 칠함으로써 이미지를 완성한다. 이 때 pixel이 여러 다각형에 겹치는 경우는 그 중 한 색깔을 선택함으로 원근을 다르게 하거나, 또는 전혀 다른 제 3의 색깔을 선택할 수도 있다

### 주의사항:

GL_TRIANGLES, GL_QUADS, GL_POLYGON 등은 절대 사용하지 않으며 반드시 GL_POINTS 만 사용한다 (점들을 찍어 그림을 그림)
image size 및 각 도형을 결정하는 데이타는 별도의 data file에서 읽어 들이는 형태로 프로그램을 구성한다

### 제출 내용:

source program 및 data file의 내용
프로그램을 실행하여 생성된 image 를 capture한 image file (반드시 color image 이어야 함 )

- circle 완료
- ellipse 완료
- bresenham 완료
