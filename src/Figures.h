#include <list>
#include <vector>
#include "Graphics.h"

class Figure
{
 protected:
  Matrix mTransform;
  float mR;
  int mTX, mTY;
  float mSX, mSY;

  Color mColor;
  bool mClip;

  void calculateTransform()
  {
  }
  
 public:
  Figure() { mR = mTX = mTY = 0; mSX = mSY = 1.0f; mColor = {0, 0, 0}; mClip = true; }

  virtual void rotate(float angle) { mR = angle; calculateTransform(); };
  virtual void translate(int tx, int ty) { mTX = tx; mTY = ty; calculateTransform(); }
  virtual void scale(float sx, float sy) { mSX = sx; mSY = sy; calculateTransform(); }

  virtual void setColor(int r, int g, int b) { mColor = {r, g, b}; }
  
  virtual void clip(bool c) { mClip = c; }
  virtual bool clip() { return mClip; }

  virtual void draw() const = 0;
  virtual void fill() const = 0;
};

class Line : public Figure
{
 public:
  Point p1, p2;

  Line(const Point& pi, const Point& pf) : p1(pi), p2(pf) {}
  Line(const Line& l) : p1(l.p1), p2(l.p2) {}
  Line& operator=(const Line& l) { p1 = l.p1; p2 = l.p2; }

  void draw() const;
  void fill() const;
};

class Oval : public Figure
{
 private:
  Point mC;
  int mRX;
  int mRY;
  
 public:
  Oval(const Point& c, int crx, int cry) : mC(c) { rx(crx); ry(cry); }
  Oval(int x, int y, int crx, int cry) : mC(Point(x, y)) { rx(crx); ry(cry); }
  Oval& operator=(const Oval& c) { mC = c.mC; mRX = c.mRX; mRY = c.mRY; }

  int x() const { return mC.x; }
  int y() const { return mC.y; }
  int rx() const { return mRX; }
  int ry() const { return mRY; }

  void x(int px) { mC.x = px; }
  void y(int py) { mC.y = py; }
  void rx(int crx) { mRX = crx > 0 ? crx : 0; }
  void ry(int cry) { mRY = cry > 0 ? cry : 0; }

  void draw() const;
  void fill() const;
};

class Rectangle : public Figure
{
 private:
  Point p1, p2;
  
 public:
  Rectangle(int x, int y, int w, int h) : p1(Point(x, y)), p2(Point(p1.x + w, p1.y + h)) {}
  Rectangle(Rectangle& r) : p1(r.p1), p2(r.p2) {}
  Rectangle& operator=(Rectangle& r) { p1 = r.p1; p2 = r.p2; }

  int x() const { return p1.x; }
  int y() const { return p1.y; }
  int width() const { return p2.x - p1.x; }
  int height() const { return p2.y - p1.y; }

  void x(int rx) { p1.x = rx; }
  void y(int ry) { p1.y = ry; }
  void width(int w) { p2.x = p1.x + w; }
  void height(int h) { p2.y = p1.y + h; }

  void draw() const;
  void fill() const;
};

class Polygon : public Figure
{
 private:
  std::vector<Point> mPoints;
  
 public:
  Polygon() {}
  Polygon(std::vector<Point> pts) : mPoints(pts) {}
  Polygon(Polygon& poly) : mPoints(poly.mPoints) {}
  Polygon& operator=(Polygon& poly) { mPoints = poly.mPoints; }

  Point& first() { return mPoints.front(); }
  Point& last() { return mPoints.back(); }
  int size() const { return mPoints.size(); }
  
  Point& at(int i) { return mPoints.at(i); }
  Point& operator[](int i) { return mPoints[i]; }
  
  void addPoint(Point p) { mPoints.push_back(p); }
  void addPoint(int x, int y) { mPoints.push_back(Point(x, y)); }

  void clear() { mPoints.clear(); }
  bool closed() const { return mPoints.size() > 2 && mPoints.front() == mPoints.back(); }

  void draw() const;
  void fill() const;
};
