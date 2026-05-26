#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>

struct Point
{
  int x, y;
};

struct Polygon
{
  std::vector<Point> points;
};

double area(const Polygon&);
bool operator==(const Polygon&, const Polygon&);
Polygon parsePolygon(const std::string&);
std::vector<Polygon> readShapesFromFile(const std::string&);

#endif
