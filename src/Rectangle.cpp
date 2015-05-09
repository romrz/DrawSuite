#include "Figures.h"

void Rectangle :: draw() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  g.rotate(mR);
  g.translate(mTX, mTY);
  g.scale(mSX, mSY);
  g.drawRectangle(p1, p2);
  g.rotate(-mR);
  g.translate(-mTX, -mTY);
  g.scale(-mSX, -mSY);
}

void Rectangle :: fill() const
{
}
