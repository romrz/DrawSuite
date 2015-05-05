#include "Figures.h"

void Rectangle :: clip()
{
}

void Rectangle :: draw() const
{
  Line(p, Point(p.x + w, p.y)).draw();
  Line(Point(p.x + w, p.y), Point(p.x + w, p.y + h)).draw();
  Line(Point(p.x + w, p.y + h), Point(p.x, p.y + h)).draw();
  Line(Point(p.x, p.y + h), p).draw();
}

void Rectangle :: fill() const
{
}
