#ifndef METHODS_H
#define METHODS_H

#include "polygon.h"

int countEven(const std::vector<Polygon>& polygons);
int countOdd(const std::vector<Polygon>& polygons);
int countByVertexCount(const std::vector<Polygon>& polygons, int vertexCount);

double maxArea(const std::vector<Polygon>& polygons);
int maxVertexCount(const std::vector<Polygon>& polygons);

double minArea(const std::vector<Polygon>& polygons);
int minVertexCount(const std::vector<Polygon>& polygons);

double sumAreaEven(const std::vector<Polygon>& polygons);
double sumAreaOdd(const std::vector<Polygon>& polygons);
double sumAreaByVertexCount(const std::vector<Polygon>& polygons, int vertexCount);
double meanArea(const std::vector<Polygon>& polygons);

int maxConsecutiveEqual(const std::vector<Polygon>& polygons, const Polygon& target);
int duplicateEcho(const std::vector<Polygon>& polygons, const Polygon& target);

#endif
