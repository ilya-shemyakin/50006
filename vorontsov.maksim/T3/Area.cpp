#include "Area.h"
#include "Count.h"
#include <numeric>
#include <cmath>
#include <functional>
#include <stdexcept>
double area(const Polygon& polygon) {
    const auto& pts = polygon.points;
    const size_t n = pts.size();
    if (n < MIN_VERTICES) {
        return 0.0;
    }
    auto it1 = pts.begin();
    auto it2 = std::next(pts.begin());
    double sum1 = std::inner_product(it1, std::prev(pts.end()), it2, 0.0,
        std::plus<double>(),
        [](const Point& a, const Point& b) {
            return static_cast<double>(a.x) * b.y;
        });
    double sum2 = std::inner_product(it1, std::prev(pts.end()), it2, 0.0,
        std::plus<double>(),
        [](const Point& a, const Point& b) {
            return static_cast<double>(a.y) * b.x;
        });
    double last = static_cast<double>(pts.back().x) * pts.front().y -
                  static_cast<double>(pts.back().y) * pts.front().x;
    return std::abs(sum1 - sum2 + last) / 2.0;
}
double sumAreaEven(const std::vector<Polygon>& polygons) {
    auto evenArea = std::bind(std::multiplies<double>(),
        std::bind(isEvenVertexCount, std::placeholders::_1),
        std::bind(area, std::placeholders::_1));
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(std::plus<double>(), std::placeholders::_1,
        std::bind(evenArea, std::placeholders::_2)));
}
double sumAreaOdd(const std::vector<Polygon>& polygons) {
    auto oddArea = std::bind(std::multiplies<double>(),
        std::bind(isOddVertexCount, std::placeholders::_1),
        std::bind(area, std::placeholders::_1));
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(std::plus<double>(), std::placeholders::_1,
        std::bind(oddArea, std::placeholders::_2)));
}
double sumAreaByVertexCount(const std::vector<Polygon>& polygons, size_t count) {
    auto correctArea = std::bind(std::multiplies<double>(),
        std::bind(isVertexCount, std::placeholders::_1, count),
        std::bind(area, std::placeholders::_1));
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(std::plus<double>(), std::placeholders::_1,
        std::bind(correctArea, std::placeholders::_2)));
}
double meanArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::runtime_error("empty");
    }
    double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
        std::bind(std::plus<double>(), std::placeholders::_1,
        std::bind(area, std::placeholders::_2)));
    return total / polygons.size();
}
