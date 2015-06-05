#include "Figures.h"

void Line :: draw() const
{
  Graphics& g = Graphics::getInstance();

  g.setColor(mColor);
  if(!mClip)
  {
    int clipType = g.getClipType();
    g.setClipType(Graphics::NO_CLIP);
    g.drawLine(p1, p2);
    g.setClipType(clipType);
  }
  else
    g.drawLine(p1, p2);
}

void Line :: fill() const {}
