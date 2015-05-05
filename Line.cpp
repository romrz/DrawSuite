#include <list>
#include "Figures.h"
#include <cmath>

void Line :: rotate(float angle)
{}

void Line :: translate(int dx, int dy)
{}

void Line :: scale(int sx, int sy)
{}

std::list<Point> Line :: getPointList() const
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

void Line :: clip()
{
}

void Line :: draw() const
{
  lineDDA(p1.x, p1.y, p2.x, p2.y);
}

void Line :: fill() const {}
