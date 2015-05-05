#include "Figures.h"

void Rectangle :: rotate(float angle)
{}

void Rectangle :: translate(int dx, int dy)
{}

void Rectangle :: scale(int sx, int sy)
{}


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
