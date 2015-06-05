#include <GL/glut.h>
#include <list>
#include <vector>
#include "Matrix.h"

struct Color
{
  int r;
  int g;
  int b;
};

class Point
{
 public:
  int x;
  int y;
  int z;

  Point(int px = 0, int py = 0, int pz = 1) : x(px), y(py), z(pz) {}
  Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}
  Point& operator=(const Point& p) { x = p.x; y = p.y; z = p.z; }
    
  bool operator<(const Point& p) const { return y < p.y; }
  bool operator==(const Point& p) const { return x == p.x && y == p.y && z == p.z; }
  Point operator+(const Point& p) const { return Point(x + p.x, y + p.y, z + p.z); }
  Point operator-(const Point& p) const { return Point(x - p.x, y - p.y, z - p.z); }
  int operator*(const Point& p) const { return x * p.x + y * p.y; }
  Point operator*(const int n) const { return Point(x * n, y * n, z * n); }
  Point operator*(const float n) const { return Point((int)((float)x * n), (int)((float)y * n), z); }
};

struct ClipPolygon
{
  std::vector<Point> points;

  void addPoint(const Point &p) { points.push_back(p); }
};

struct ClipRectangle
{
  int xmin, ymin, xmax, ymax;
};

class Graphics
{
 private:
  int mClipType;
  ClipPolygon mClipPoly;
  ClipRectangle mClipRect;

  Matrix mTransform;

  Graphics() {}

  // DDA algorithm for line drawing
  void DDALine(const Point& p1, const Point& p2) const;
  // Clipping Algorithms
  bool clipLineLiangBarsky(Point& p1, Point& p2) const;
  bool clipLineCyrusBeck(Point& p1, Point& p2) const;

 public:
  static const int NO_CLIP = 0, CLIP_RECT = 1, CLIP_POLY = 2;
  
  // Singleton
  static Graphics& getInstance()
  {
    static Graphics mInstance;
    return mInstance;
  }

  void setColor(const Color &c) { glColor3f(c.r/255.0, c.g/255.0, c.b/255.0); }
  void setColor(int r, int g, int b) { glColor3f(r/255.0, g/255.0, b/255.0); }

  void rotate(float r);
  void translate(int tx, int ty);
  void scale(float sx, float sy);
  void setTransformMatrix(Matrix& transform) { mTransform = transform; }

  void setClipType(int clipType) { mClipType = clipType; }
  int getClipType() { return mClipType; }
  void setClipArea(ClipRectangle &c) { mClipRect = c; mClipType = CLIP_RECT; }
  void setClipArea(ClipPolygon &c) { mClipPoly = c; mClipType = CLIP_POLY; }

  std::list<Point> getLinePoints(const Point &p1, const Point &p2) const;
  void drawLine(Point p1, Point p2) const;
  
  void drawTriangle(const Point &p1, const Point &p2, const Point &p3) const;
  void fillTriangle(const Point &p1, const Point &p2, const Point &p3) const;
  
  void drawRectangle(const Point &p1, const Point &p2) const;
  void fillRectangle(const Point &p1, const Point &p2) const;
  
  void drawOval(const Point &p, int rx, int ry) const;
  void fillOval(const Point &p, int rx, int ry) const;
  
  void drawPolygon(const std::vector<Point> &points) const;
  void fillPolygon(const std::vector<Point> &points) const;
};
