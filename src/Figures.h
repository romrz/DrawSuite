#include <list>
#include <vector>
#include "Graphics.h"

class Figure
{
 protected:
  float mR = 0.0f;
  int mTX = 0, mTY = 0;
  float mSX = 1.0f, mSY = 1.0f;

  Color mColor = {0, 0, 0};
  
 public:

  virtual void rotate(float angle) { mR = angle; };
  virtual void translate(int tx, int ty) { mTX = tx; mTY = ty; }
  virtual void scale(float sx, float sy) { mSX = sx; mSY = sy; }

  virtual void setColor(int r, int g, int b) { mColor = {r, g, b}; }
  
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

class Circle : public Figure
{
 private:
  Point mC;
  int mR;
  
 public:
  Circle(const Point& c, int cr) : mC(c), mR(cr > 0 ? cr : 0) {}
  Circle(int x, int y, int cr) : mC(Point(x, y)), mR(cr > 0 ? cr : 0) {}
  Circle& operator=(const Circle& c) { mC = c.mC; mR = c.mR; }

  int x() const { return mC.x; }
  int y() const { return mC.y; }
  int r() const { return mR; }

  void x(int px) { mC.x = px; }
  void y(int py) { mC.y = py; }
  void r(int cr) { mR = cr > 0 ? cr : 0; }

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
