#include "Count.h"
#include <algorithm>
#include <functional>
size_t getVertexCount(const Polygon& polygon) {
    return polygon.points.size();
}
bool isEvenVertexCount(const Polygon& polygon) {
    return polygon.points.size() % 2 == 0;
}
bool isOddVertexCount(const Polygon& polygon) {
    return polygon.points.size() % 2 != 0;
}
bool isVertexCount(const Polygon& polygon, size_t count) {
    return polygon.points.size() == count;
}
int countEven(const std::vector<Polygon>& polygons) {
    return std::count_if(polygons.begin(), polygons.end(), isEvenVertexCount);
}
int countOdd(const std::vector<Polygon>& polygons) {
    return std::count_if(polygons.begin(), polygons.end(), isOddVertexCount);
}
int countByVertexCount(const std::vector<Polygon>& polygons, size_t count) {
    auto pred = std::bind(std::equal_to<size_t>(),
        std::bind(getVertexCount, std::placeholders::_1), count);
    return std::count_if(polygons.begin(), polygons.end(), pred);
}
