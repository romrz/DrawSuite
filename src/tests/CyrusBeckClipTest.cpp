#include <iostream>
#include "../Figures.h"

void onDisplay();
void onClick(int button, int state, int x, int y);
void onMove(int x, int y);

const int WIDTH = 500;
const int HEIGHT = 500;

ClipPolygon clipArea;
Polygon polygon;

Line clipLine(Point(0, 0), Point(0,0));
Line line(Point(0, 0), Point(0,0));

int main()
{
  int a;
  glutInit(&a, NULL);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Cyrus-Beck Algorithm");

  glutDisplayFunc(onDisplay);
  glutMouseFunc(onClick);
  glutMotionFunc(onMove);
  
  glClearColor(1, 1, 1, 0);
  glViewport(0, 0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  // Set ClipArea's points
  clipArea.addPoint(Point(200, 100));
  clipArea.addPoint(Point(100, 200));
  clipArea.addPoint(Point(100, 300));
  clipArea.addPoint(Point(200, 400));
  clipArea.addPoint(Point(300, 400));
  clipArea.addPoint(Point(400, 300));
  clipArea.addPoint(Point(400, 200));
  clipArea.addPoint(Point(300, 100));
  clipArea.addPoint(Point(200, 100));
  
  Graphics::getInstance().setClipArea(clipArea);

  Polygon temp(clipArea.points);
  polygon = temp;
  polygon.setColor(0, 0, 255);

  clipLine.setColor(255, 0, 0);
  line.setColor(0, 255, 0);
  line.clip(false);

  glutMainLoop();
  return 0;
}

void onDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);

  polygon.draw();
  line.draw();
  clipLine.draw();

  glFlush();
}

void onClick(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    y = HEIGHT - y;

    Point p(x, y);

    clipLine.p1 = p;
    clipLine.p2 = p;

    line.p1 = p;
    line.p2 = p;
  }
  
  glutPostRedisplay();
}

void onMove(int x, int y)
{
  y = HEIGHT - y;
  
  clipLine.p2 = Point(x, y);
  line.p2 = Point(x, y);
  
  glutPostRedisplay();
}
