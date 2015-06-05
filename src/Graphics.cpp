#include "Graphics.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

void Graphics::rotate(float r)
{
}

void Graphics::translate(int tx, int ty)
{
}

void Graphics::scale(float sx, float sy)
{
}

void Graphics::drawLine(Point p1, Point p2) const
{
  bool clip = true;
  if(mClipType == CLIP_RECT)
    clip = clipLineLiangBarsky(p1, p2);
  else if(mClipType == CLIP_POLY)
    clip = clipLineCyrusBeck(p1, p2);

  if(clip)
    DDALine(p1, p2);
}

bool Graphics::clipLineCyrusBeck(Point &p1, Point &p2) const
{
  Point D = p2 - p1, n, w, p, f, v; // Vectors
  float ti = 0.0f, tf = 1.0f, t;
  int size = mClipPoly.points.size();
  int num, den;
  
  for(int i = 0; i < size; i++) {
    if(i == 0)
      v = mClipPoly.points[size - 1] - mClipPoly.points[i];
    else
      v = mClipPoly.points[i - 1] - mClipPoly.points[i];

    n = Point(-v.y, v.x);
    f = mClipPoly.points[i];
    w = p1 - f;

    num = n * w;
    den = n * D;
    if(num == 0 && den < 0) return false;
    
    t = -(float)num / (float)den;
    if(t >= 0 && t <= 1)
      if(den < 0) {
	if(t < tf) tf = t; }
      else if(den > 0)
	if(t > ti) ti = t;
  }
  if(ti > tf) return false;
  
  Point np1 = p1 + (p2 - p1) * ti;
  Point np2 = p1 + (p2 - p1) * tf;
  p1 = np1;
  p2 = np2;
}

bool Graphics::clipLineLiangBarsky(Point& p1, Point& p2) const
{
  int p[] = {
    -p2.x + p1.x, // -dx
    p2.x - p1.x,  // dx
    -p2.y + p1.y, // -dy
    p2.y - p1.y   // dy
  };
  int q[] = {
    p1.x - mClipRect.xmin, // xi - xmin
    mClipRect.xmax - p1.x, // xmax - xi
    p1.y - mClipRect.ymin, // yi - ymin
    mClipRect.ymax - p1.y  // ymax - ymin
  };

  float ui = 0.0f, uf = 1.0f;
  for(int i = 0; i < 4; i++)
  {
    if(p[i] == 0 && q[i] < 0)
      return false;
    if(p[i] == 0)
      continue;
    
    float u = (float)q[i] / (float)p[i];
    if(p[i] < 0) {
      if(u > ui) ui = u; }
    else
      if(u < uf) uf = u;
  }
  if(uf < ui) return false;
  
  Point np1 = p1 + (p2 - p1) * ui;
  Point np2 = p1 + (p2 - p1) * uf;
  p1 = np1;
  p2 = np2;
}

void Graphics::DDALine(const Point &p1, const Point &p2) const
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

    glVertex2f(x, y);
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
  Point pt1 = p1;
  Point pt2 = p2;

  drawLine(pt1, Point(pt2.x, pt1.y));
  drawLine(Point(pt2.x, pt1.y), Point(pt2.x, pt2.y));
  drawLine(Point(pt2.x, pt2.y), Point(pt1.x, pt2.y));
  drawLine(Point(pt1.x, pt2.y), pt1);
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
  
  glVertex2f(x0, y0 + ry);
  glVertex2f(x0, y0 - ry);
  
  while(twoRy2 * x < twoRx2 * y) {
    x++;
    
    if(p < 0)
      p += twoRy2 * x + ry2;
    else
      p += twoRy2 * x + ry2 - twoRx2 * (--y);

    glVertex2f(x0 + x, y0 + y);
    glVertex2f(x0 - x, y0 + y);
    glVertex2f(x0 + x, y0 - y);
    glVertex2f(x0 - x, y0 - y);
  }
  
  p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);

  while(y > 0) {
    y--;
    
    if(p > 0)
      p += -twoRx2 * y + rx2;
    else
      p += twoRy2 * (++x) - twoRx2 * y + rx2;

    glVertex2f(x0 + x, y0 + y);
    glVertex2f(x0 - x, y0 + y);
    glVertex2f(x0 + x, y0 - y);
    glVertex2f(x0 - x, y0 - y);
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
