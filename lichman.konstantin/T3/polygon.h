#ifndef POLYGON_H
#define POLYGON_H

#include <iosfwd>
#include <vector>

struct Point {
    int x;
    int y;
};

struct Polygon {
    std::vector<Point> points;
};

struct DelimiterIo {
    char exp;
};

std::istream& operator>>(std::istream& in, const DelimiterIo& dest);
std::istream& operator>>(std::istream& in, Point& point);
std::istream& operator>>(std::istream& in, Polygon& polygon);

bool operator==(const Point& lhs, const Point& rhs);
bool operator==(const Polygon& lhs, const Polygon& rhs);

#endif
