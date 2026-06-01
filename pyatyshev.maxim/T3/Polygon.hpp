#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <string>

struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

struct Polygon {
    std::vector<Point> points;
};

double area(const Polygon& p);
bool operator==(const Polygon& a, const Polygon& b);
Polygon parsePolygon(const std::string& str);
std::vector<Polygon> readShapesFromFile(const std::string& filename);


bool isRectangle(const Polygon& p);


bool isSameShape(const Polygon& a, const Polygon& b);
Polygon normalizeByMinPoint(const Polygon& p);

#endif
