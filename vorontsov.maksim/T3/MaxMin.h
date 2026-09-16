#ifndef MAXMIN_H
#define MAXMIN_H
#include <vector>
#include "Structs.h"

double maxArea(const std::vector<Polygon>& polygons);
size_t maxVertexCount(const std::vector<Polygon>& polygons);
double minArea(const std::vector<Polygon>& polygons);
size_t minVertexCount(const std::vector<Polygon>& polygons);
#endif
