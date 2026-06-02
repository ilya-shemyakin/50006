#ifndef AREA_H
#define AREA_H
#include <vector>
#include "Structs.h"
double area(const Polygon& polygon);
double sumAreaEven(const std::vector<Polygon>& polygons);
double sumAreaOdd(const std::vector<Polygon>& polygons);
double sumAreaByVertexCount(const std::vector<Polygon>& polygons, size_t count);
double meanArea(const std::vector<Polygon>& polygons);
#endif
