#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Polygon.hpp"


int countEven(const std::vector<Polygon>& figures);
int countOdd(const std::vector<Polygon>& figures);
int countByVertexCount(const std::vector<Polygon>& figures, int vertexCount);


double sumAreaEven(const std::vector<Polygon>& figures);
double sumAreaOdd(const std::vector<Polygon>& figures);
double sumAreaByVertexCount(const std::vector<Polygon>& figures, int vertexCount);
double meanArea(const std::vector<Polygon>& figures);


double maxArea(const std::vector<Polygon>& figures);
int maxVertexCount(const std::vector<Polygon>& figures);

double minArea(const std::vector<Polygon>& figures);
int minVertexCount(const std::vector<Polygon>& figures);


int countRectangles(const std::vector<Polygon>& figures);


int countSameShape(const std::vector<Polygon>& figures, const Polygon& target);

#endif

