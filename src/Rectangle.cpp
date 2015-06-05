#include "Figures.h"

void Rectangle :: draw() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  if(!mClip)
  {
    int clipType = g.getClipType();
    g.setClipType(Graphics::NO_CLIP);
    g.drawRectangle(p1, p2);
    g.setClipType(clipType);
  }
  else
    g.drawRectangle(p1, p2);
}

void Rectangle :: fill() const
{
}
