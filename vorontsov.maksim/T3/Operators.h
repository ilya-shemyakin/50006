#ifndef OPERATORS_H
#define OPERATORS_H
#include <iostream>
#include "Structs.h"

std::istream& operator>>(std::istream& stream, Point& point);
std::istream& operator>>(std::istream& stream, Polygon& polygon);
std::ostream& operator<<(std::ostream& stream, const Point& point);
std::ostream& operator<<(std::ostream& stream, const Polygon& polygon);
bool operator==(const Polygon& left, const Polygon& right);
#endif
