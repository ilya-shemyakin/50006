#include "MaxMin.h"
#include "Area.h"
#include "Count.h"
#include <algorithm>
#include <functional>
#include <stdexcept>
double maxArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::runtime_error("empty");
    }
    auto pred = std::bind(std::less<double>(),
        std::bind(area, std::placeholders::_1),
        std::bind(area, std::placeholders::_2));
    auto it = std::max_element(polygons.begin(), polygons.end(), pred);
    return area(*it);
}
size_t maxVertexCount(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::runtime_error("empty");
    }
    auto pred = std::bind(std::less<size_t>(),
        std::bind(getVertexCount, std::placeholders::_1),
        std::bind(getVertexCount, std::placeholders::_2));
    auto it = std::max_element(polygons.begin(), polygons.end(), pred);
    return getVertexCount(*it);
}
double minArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::runtime_error("empty");
    }
    auto pred = std::bind(std::less<double>(),
        std::bind(area, std::placeholders::_1),
        std::bind(area, std::placeholders::_2));
    auto it = std::min_element(polygons.begin(), polygons.end(), pred);
    return area(*it);
}
size_t minVertexCount(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::runtime_error("empty");
    }
    auto pred = std::bind(std::less<size_t>(),
        std::bind(getVertexCount, std::placeholders::_1),
        std::bind(getVertexCount, std::placeholders::_2));
    auto it = std::min_element(polygons.begin(), polygons.end(), pred);
    return getVertexCount(*it);
}
