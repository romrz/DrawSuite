#include "Figures.h"

bool operator<(const Point& p1, const Point& p2)
{
  return p1.y < p2.y;
}

bool operator==(const Point& p1, const Point& p2)
{
  return p1.x == p2.x && p1.y == p2.y && p1.z == p2.z;
}
