#include "Figures.h"

void Polygon :: draw() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  g.rotate(mR);
  g.translate(mTX, mTY);
  g.scale(mSX, mSY);
  g.drawPolygon(mPoints);
  g.rotate(-mR);
  g.translate(-mTX, -mTY);
  g.scale(-mSX, -mSY);
}

void Polygon :: fill() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  g.rotate(mR);
  g.translate(mTX, mTY);
  g.scale(mSX, mSY);
  g.fillPolygon(mPoints);
  g.rotate(-mR);
  g.translate(-mTX, -mTY);
  g.scale(-mSX, -mSY);
}
