#include "GraphicsAlgorithms.h"
#include <GL/gl.h>
#include <cmath>

void lineDDA(int x1, int y1, int x2, int y2)
{
  glBegin(GL_POINTS);
  
  int dx = x2 - x1, dy = y2 - y1, steps, k;
  float xIncrement, yIncrement, x = x1, y = y1;

  if(fabs(dx) > fabs(dy))
    steps = fabs(dx);
  else
    steps = fabs(dy);

  xIncrement = (float) dx / (float) steps;
  yIncrement = (float) dy / (float) steps;

  glVertex2i(x, y);

  for(k = 0; k < steps; k++) {
    x += xIncrement;
    y += yIncrement;

    glVertex2i(x, y);
  }

  glEnd();
}

void lineBresenham(int x1, int y1, int x2, int y2)
{
  glBegin(GL_POINTS);
  
  int dx = x2 - x1, dy = y2 - y1, x = x1, y = y1;
  int xFactor = 0, yFactor = 0, k, steps, c1, c2, p;
  int xIncrement = dx > 0 ? 1 : -1;
  int yIncrement = dy > 0 ? 1 : -1;

  dx = std::abs(dx);
  dy = std::abs(dy);

  if(dx > dy) {
    steps = dx;
    c1 = 2 * dy - 2 * dx;
    c2 = 2 * dy;
    p = 2 * dy - dx;
    xFactor = 1;
  } else {
    steps = dy;
    c1 = 2 * dx - 2 * dy;
    c2 = 2 * dx;
    p = 2 * dx - dy;
    yFactor = 1;
  }
  
  glVertex2i(x, y);

  for(k = 0; k < steps; k++) {
    if(p < 0) {
      x += xIncrement * xFactor;
      y += yIncrement * yFactor;
      p = p + c2;
    } else {
      x += xIncrement;
      y += yIncrement;
      p = p + c1;
    }

    glVertex2i(x, y);
  }

  glEnd();
}

void circle(int x0, int y0, int r)
{
  glBegin(GL_POINTS);
  
  int x = 0, y = r, p = 1 - r;

  glVertex2i(x0, y0 + r);
  glVertex2i(x0 + r, y0);
  glVertex2i(x0 - r, y0);
  glVertex2i(x0, y0 - r);

  while(x < y) {
    x++;

    if(p < 0)
      p += 2 * x + 1;
    else
      p += 2 * (x - --y) + 1;

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
    
    glVertex2i(x0 + y, y0 + x);
    glVertex2i(x0 - y, y0 + x);
    glVertex2i(x0 + y, y0 - x);
    glVertex2i(x0 - y, y0 - x);
  }

  glEnd();
}

void ellipse(int x0, int y0, int rx, int ry)
{
  glBegin(GL_POINTS);
  
  long x = 0, y = ry;
  long rx2 = rx * rx, ry2 = ry * ry;
  long twoRx2 = 2 * rx2, twoRy2 = 2 * ry2;
  long p = round(ry2 - rx2 * ry + rx2 * 0.25);

  glVertex2i(x0, y0 + ry);
  glVertex2i(x0, y0 - ry);
  
  while(twoRy2 * x < twoRx2 * y) {
    x++;
    
    if(p < 0)
      p += twoRy2 * x + ry2;
    else
      p += twoRy2 * x + ry2 - twoRx2 * (--y);

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
  }
  
  p = round(ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2);

  while(y > 0) {
    y--;
    
    if(p > 0)
      p += -twoRx2 * y + rx2;
    else
      p += twoRy2 * (++x) - twoRx2 * y + rx2;

    glVertex2i(x0 + x, y0 + y);
    glVertex2i(x0 - x, y0 + y);
    glVertex2i(x0 + x, y0 - y);
    glVertex2i(x0 - x, y0 - y);
  }

  glEnd();
}
