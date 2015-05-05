#include "Figures.h"

void Polygon :: rotate(float angle)
{}

void Polygon :: translate(int dx, int dy)
{}

void Polygon :: scale(int sx, int sy)
{}


void Polygon :: clip()
{
}

void Polygon :: draw() const
{
  for(int i = 0; i < (int) points.size() - 1; i++)
    Line(points[i], points[i+1]).draw();
}

void Polygon :: fill() const
{
  std::list<Point> pointList;
  std::list<Point>::iterator it = pointList.begin();
  
  std::list<Point> aux;
  std::list<Point>::iterator itaux;
  
  for(int i = 0; i < (int) points.size() - 1; i++) {
    aux = Line(points[i], points[i+1]).getPointList();
    pointList.insert(it, aux.begin(), aux.end());
  }
  
  pointList.sort();

  for(it = pointList.begin(); it != pointList.end();) {
    Point p1 = *it;
    if(++it != pointList.end())
      Line(p1, *it).draw();
  }
}
