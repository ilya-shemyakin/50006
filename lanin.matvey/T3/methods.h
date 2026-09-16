#ifndef METHODS_H
#define METHODS_H

#include "polygon.h"

#include <cstddef>
#include <iosfwd>
#include <vector>

std::vector<Polygon> readPolygons(std::istream& in);

double getArea(const Polygon& polygon);
double getAreaByParity(const std::vector<Polygon>& polygons, std::size_t parity);
double getAreaByVertexCount(const std::vector<Polygon>& polygons, std::size_t count);
double getMeanArea(const std::vector<Polygon>& polygons);
double getMaxArea(const std::vector<Polygon>& polygons);
double getMinArea(const std::vector<Polygon>& polygons);

std::size_t getMaxVertexCount(const std::vector<Polygon>& polygons);
std::size_t getMinVertexCount(const std::vector<Polygon>& polygons);
std::size_t countByParity(const std::vector<Polygon>& polygons, std::size_t parity);
std::size_t countByVertexCount(const std::vector<Polygon>& polygons, std::size_t count);

std::size_t echoPolygon(std::vector<Polygon>& polygons, const Polygon& target);
std::size_t maxSeq(const std::vector<Polygon>& polygons, const Polygon& target);

#endif
