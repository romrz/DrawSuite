#include <iostream>
#include <GL/glut.h>
#include "../src/Figures.h"

void onDisplay();
void onClick(int button, int state, int x, int y);
void onMove(int x, int y);
void onPassiveMove(int x, int y);

const int WIDTH = 500;
const int HEIGHT = 500;

Polygon polygon;
bool showBoundRect = false;

int main()
{
  int a;
  glutInit(&a, NULL);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Polygon");

  glutDisplayFunc(onDisplay);
  glutMouseFunc(onClick);
  glutMotionFunc(onMove);
  glutPassiveMotionFunc(onPassiveMove);
  
  glClearColor(1, 1, 1, 0);
  glViewport(0, 0, WIDTH, HEIGHT);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, WIDTH, 0, HEIGHT);

  glutMainLoop();
    
  return 0;
}

void onDisplay()
{
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1, 0, 0);

  polygon.draw();
  
  if(polygon.closed())
    polygon.fill();

  if(showBoundRect)
    Rectangle(polygon.first().x - 10, polygon.first().y - 10, 20 , 20).draw();

  glFlush();
}

void onClick(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    if(polygon.closed())
      polygon.clear();
    
    if(showBoundRect)
      polygon.addPoint(polygon.first());
    else
      polygon.addPoint(Point(x, HEIGHT - y));
  }
  
  glutPostRedisplay();
}

void onMove(int x, int y)
{
  y = HEIGHT - y;
  
  if(polygon.size() == 1) polygon.addPoint(x, y);

  polygon.last() = Point(x, y);

  showBoundRect = (polygon.first().x > x - 10 &&
		   polygon.first().x < x + 10 &&
		   polygon.first().y > y - 10 &&
		   polygon.first().y < y + 10);
  if(showBoundRect)
    polygon.last() = Point(polygon.first());
  
  glutPostRedisplay();
}

void onPassiveMove(int x, int y)
{
  y = HEIGHT - y;
  
  showBoundRect = (polygon.size() > 0 &&
		   polygon.first().x > x - 10 &&
		   polygon.first().x < x + 10 &&
		   polygon.first().y > y - 10 &&
		   polygon.first().y < y + 10);
  
  glutPostRedisplay();
}
