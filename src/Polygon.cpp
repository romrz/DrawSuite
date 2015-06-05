#include "Figures.h"

void Polygon :: draw() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  g.drawPolygon(mPoints);
}

void Polygon :: fill() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  g.fillPolygon(mPoints);
}
