#include <list>
#include "Figures.h"
#include <cmath>

void Line :: draw() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  g.rotate(mR);
  g.translate(mTX, mTY);
  g.scale(mSX, mSY);
  g.drawLine(p1, p2);
  g.rotate(-mR);
  g.translate(-mTX, -mTY);
  g.scale(-mSX, -mSY);
}

void Line :: fill() const {}
