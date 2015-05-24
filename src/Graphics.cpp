#include "Graphics.h"
#include <iostream>
#include <cmath>

void Graphics::rotate(float r)
{
}

void Graphics::translate(int tx, int ty)
{
}

void Graphics::scale(float sx, float sy)
{
}

bool Graphics::clipLine(const Point &p1, const Point &p2) const
{
  Point D = p2 - p1, n, w, p, f;
  float ti = 0.0f, tf = 0.0f, temp;

  for(int i = 1; i < mClipArea.points.size(); i++) {
    Point ab = mClipArea.points[i-1] - mClipArea.points[i];
    
    n = Point(-ab.y, ab.x);

    f = mClipArea.points[i-1];
    w = p1 - f;

    temp = -(float)(n*w)/(float)(n*D);

    if(n*D < 0) {
      tf = temp < tf ? temp : tf;
    }
    else if(n*D > 0) {
      ti = temp > ti ? temp : ti;
    }
  }

  Point np1 = p1 + (p2 - p1) * round(ti);
  Point np2 = p1 + (p2 - p1) * round(tf);

  std::cout << "p1( " << np1.x << ", " << np1.y  <<  " )" << std::endl;
  std::cout << "p2( " << np2.x << ", " << np2.y  <<  " )" << std::endl;

  drawLine(np1, np2);
}

void Graphics::drawLine(const Point &p1, const Point &p2) const
{
  glBegin(GL_POINTS);
  
  int dx = p2.x - p1.x, dy = p2.y - p1.y, steps, k;
  float xIncrement, yIncrement, x = p1.x, y = p1.y;

  if(fabs(dx) > fabs(dy))
    steps = fabs(dx);
  else
    steps = fabs(dy);

  xIncrement = (float) dx / (float) steps;
  yIncrement = (float) dy / (float) steps;

  glVertex2i(x, y);

  for(k = 0; k < steps; k++) {
    x += xIncrement;
    y += yIncrement;

    glVertex2i(x, y);
  }

  glEnd();
}
  
void Graphics::drawTriangle(const Point &p1, const Point &p2, const Point &p3) const
{
}

void Graphics::fillTriangle(const Point &p1, const Point &p2, const Point &p3) const
{
}
  
void Graphics::drawRectangle(const Point &p1, const Point &p2) const
{
  drawLine(p1, Point(p2.x, p1.y));
  drawLine(Point(p2.x, p1.y), Point(p2.x, p2.y));
  drawLine(Point(p2.x, p2.y), Point(p1.x, p2.y));
  drawLine(Point(p1.x, p2.y), p1);
}

void Graphics::fillRectangle(const Point &p1, const Point &p2) const
{
}
  
void Graphics::drawOval(const Point &point, int rx, int ry) const
{
  glBegin(GL_POINTS);
  
  long x = 0, y = ry;
  long rx2 = rx * rx, ry2 = ry * ry;
  long twoRx2 = 2 * rx2, twoRy2 = 2 * ry2;
  long p = round(ry2 - rx2 * ry + rx2 * 0.25);
  int x0 = point.x, y0 = point.y;
  
  glVertex2i(x0, y0 + ry);
  glVertex2i(x0, y0 - ry);
  
  while(twoRy2 * x < twoRx2 * y) {
    x++;
    
    if(p < 0)
      p += twoRy2 * x + ry2;
    else
      p += twoRy2 * x + ry2 - twoRx2 * (--y);

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
  }
  
  p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);

  while(y > 0) {
    y--;
    
    if(p > 0)
      p += -twoRx2 * y + rx2;
    else
      p += twoRy2 * (++x) - twoRx2 * y + rx2;

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
  }

  glEnd();
}

void Graphics::fillOval(const Point &p, int rx, int ry) const
{
}
  
void Graphics::drawPolygon(const std::vector<Point> &points) const
{
  for(int i = 0; i < (int) points.size() - 1; i++)
    drawLine(points[i], points[i+1]);
}

std::list<Point> Graphics::getLinePoints(const Point &p1, const Point &p2) const
{
  std::list<Point> points;
  
  int dx = p2.x - p1.x, dy = p2.y - p1.y, steps, k;
  float xIncrement, yIncrement, x = p1.x, y = p1.y;

  if(fabs(dx) > fabs(dy))
    steps = fabs(dx);
  else
    steps = fabs(dy);

  xIncrement = (float) dx / (float) steps;
  yIncrement = (float) dy / (float) steps;

  points.push_back(Point(x, y));

  for(k = 0; k < steps; k++) {
    x += xIncrement;
    y += yIncrement;

    points.push_back(Point(x, y));
  }

  return points;
}

void Graphics::fillPolygon(const std::vector<Point> &points) const
{
  std::list<Point> pointList;
  std::list<Point>::iterator it = pointList.begin();
  
  std::list<Point> aux;
  std::list<Point>::iterator itaux;
  
  for(int i = 0; i < (int) points.size() - 1; i++) {
    aux = getLinePoints(points[i], points[i+1]);
    pointList.insert(it, aux.begin(), aux.end());
  }
  
  pointList.sort();

  for(it = pointList.begin(); it != pointList.end();) {
    Point p1 = *it;
    if(++it != pointList.end())
      drawLine(p1, *it);
  }
}
