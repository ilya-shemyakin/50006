#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <iostream>
#include <string>

struct Point {
    int x, y;
    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const; 
};

struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const;
};

std::istream& operator>>(std::istream& is, Point& p);
std::istream& operator>>(std::istream& in, Polygon& poly);

Polygon parsePolygon(const std::string& str);
double polygonArea(const Polygon& p);
int distSq(const Point& a, const Point& b);
bool isRectangle(const Polygon& p);
Polygon normalizeByMinPoint(const Polygon& p);
bool isSameShape(const Polygon& a, const Polygon& b);

#endif
