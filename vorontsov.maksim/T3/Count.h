#ifndef COUNT_H
#define COUNT_H
#include <vector>
#include "Structs.h"

size_t getVertexCount(const Polygon& polygon);
bool isEvenVertexCount(const Polygon& polygon);
bool isOddVertexCount(const Polygon& polygon);
bool isVertexCount(const Polygon& polygon, size_t count);
int countEven(const std::vector<Polygon>& polygons);
int countOdd(const std::vector<Polygon>& polygons);
int countByVertexCount(const std::vector<Polygon>& polygons, size_t count);
#endif
