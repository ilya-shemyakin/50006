#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>

struct Point {
    int x;
    int y;
};

struct Polygon {
    std::vector<Point> points;
};

std::istream& operator>>(std::istream& in, Point& point);
std::istream& operator>>(std::istream& in, Polygon& polygon);

#endif
