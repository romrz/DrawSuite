#include <list>
#include <vector>
#include "GraphicsAlgorithms.h"

class Figure
{
 public:

  virtual void rotate(float angle) = 0;
  virtual void translate(int dx, int dy) = 0;
  virtual void scale(int sx, int sy) = 0;
  
  virtual void clip() = 0;
  virtual void draw() const = 0;
  virtual void fill() const = 0;
};

class Point
{
 public:
  int x;
  int y;
  int z;

  Point(int px = 0, int py = 0, int pz = 0) : x(px), y(py), z(pz) {}
  Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}
  Point& operator=(const Point& p) { x = p.x; y = p.y; z = p.z; }

  friend bool operator<(const Point& p1, const Point& p2);
  friend bool operator==(const Point& p1, const Point& p2);
};

class Line : public Figure
{
 public:
  Point p1;
  Point p2;

  Line(const Point& pi, const Point& pf) : p1(pi), p2(pf) {}
  Line(const Line& l) : p1(l.p1), p2(l.p2) {}
  Line& operator=(const Line& l) { p1 = l.p1; p2 = l.p2; }

  std::list<Point> getPointList() const;

  void rotate(float angle);
  void translate(int dx, int dy);
  void scale(int sx, int sy);
  
  void clip();
  void draw() const;
  void fill() const;
};

class Circle : public Figure
{
 private:
  Point p;
  int radius;
  
 public:
  Circle(const Point& c, int cr) : p(c)
  {
    radius = cr > 0 ? cr : 0;
  }
  Circle(int x, int y, int cr) : p(Point(x, y))
  {
    radius = cr > 0 ? cr : 0;
  }
  Circle& operator=(const Circle& c) { p = c.p; radius = c.radius; }

  int x() const { return p.x; }
  int y() const { return p.y; }
  int r() const { return radius; }

  void x(int px) { p.x = px; }
  void y(int py) { p.y = py; }
  void r(int cr) { radius = cr > 0 ? cr : 0; }

  void rotate(float angle);
  void translate(int dx, int dy);
  void scale(int sx, int sy);
  
  void clip();
  void draw() const;
  void fill() const;
};

class Polygon : public Figure
{
 private:
  std::vector<Point> points;
  
 public:
  Polygon() {}
  Polygon(std::vector<Point> pts) : points(pts) {}
  Polygon(Polygon& poly) : points(poly.points) {}
  Polygon& operator=(Polygon& poly) { points = poly.points; }

  Point& first() { return points.front(); }
  Point& last() { return points.back(); }
  int size() const { return points.size(); }
  
  Point& at(int i) { return points.at(i); }
  Point& operator[](int i) { return points[i]; }
  
  void addPoint(Point p) { points.push_back(p); }
  void addPoint(int x, int y) { points.push_back(Point(x, y)); }

  void clear() { points.clear(); }
  bool closed() const { return points.size() > 2 && points.front() == points.back(); }

  void rotate(float angle);
  void translate(int dx, int dy);
  void scale(int sx, int sy);
  
  void clip();
  void draw() const;
  void fill() const;
};

class Rectangle : Figure
{
 private:
  Point p;
  int w;
  int h;
  
 public:
  Rectangle(int x, int y, int wr, int hr) : p(Point(x, y))
  {
    w = wr > 0 ? wr : 0;
    h = hr > 0 ? hr : 0;
  }
  Rectangle(Point pt, int wr, int hr) : p(pt)
  {
    w = wr > 0 ? wr : 0;
    h = hr > 0 ? hr : 0;
  }
  Rectangle(Rectangle& r) : p(r.p), w(r.w), h(r.h) {}
  Rectangle& operator=(Rectangle& r)
  {
    p = r.p;
    w = r.w;
    h = r.h;
  }

  int x() const { return p.x; }
  int y() const { return p.y; }
  int width() const { return w; }
  int height() const { return h; }

  void x(int rx) { p.x = rx; }
  void y(int ry) { p.y = ry; }
  void width(int wr) { w = wr > 0 ? wr : 0; }
  void height(int hr) { h = hr > 0 ? hr : 0; }

  void rotate(float angle);
  void translate(int dx, int dy);
  void scale(int sx, int sy);
  
  void clip();
  void draw() const;
  void fill() const;
};
