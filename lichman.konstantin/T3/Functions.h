#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Polygon.h"
#include <vector>

int getVertexCount(const Polygon& p);

size_t countEven(const std::vector<Polygon>& figures);
size_t countOdd(const std::vector<Polygon>& figures);
size_t countByVertexCount(const std::vector<Polygon>& figures, size_t vertexCount);

double sumAreaEven(const std::vector<Polygon>& figures);
double sumAreaOdd(const std::vector<Polygon>& figures);
double sumAreaByVertexCount(const std::vector<Polygon>& figures, size_t vertexCount);
double meanArea(const std::vector<Polygon>& figures);

double maxArea(const std::vector<Polygon>& figures);
size_t maxVertexCount(const std::vector<Polygon>& figures);

double minArea(const std::vector<Polygon>& figures);
size_t minVertexCount(const std::vector<Polygon>& figures);

size_t countRectangles(const std::vector<Polygon>& figures);
size_t countSameShape(const std::vector<Polygon>& figures, const Polygon& target);

#endif
