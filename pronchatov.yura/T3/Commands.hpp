#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "Polygon.hpp"

#include <cstddef>
#include <vector>

double calculateArea(const Polygon& polygon);
double calculateAreaByNumberOfVertices(
    const std::vector<Polygon>& polygons,
    std::size_t numberOfVertexes
);
double calculateAreaEven(const std::vector<Polygon>& polygons);
double calculateAreaOdd(const std::vector<Polygon>& polygons);
double calculateAreaMean(const std::vector<Polygon>& polygons);
double calculateMaxArea(const std::vector<Polygon>& polygons);
double calculateMinArea(const std::vector<Polygon>& polygons);

std::size_t calculateMaxVertices(const std::vector<Polygon>& polygons);
std::size_t calculateMinVertices(const std::vector<Polygon>& polygons);

std::size_t countEven(const std::vector<Polygon>& polygons);
std::size_t countOdd(const std::vector<Polygon>& polygons);
std::size_t countByNumberOfVertices(const std::vector<Polygon>& polygons, std::size_t sizeExpected);
std::size_t countPermutations(const std::vector<Polygon>& polygons, const Polygon& targetPolygon);

bool isPermutation(const Polygon& first, const Polygon& second);
bool checkInFrame(const std::vector<Polygon>& polygons, const Polygon& targetPolygon);

#endif
