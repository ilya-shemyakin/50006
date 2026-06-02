#include "Functions.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

int getVertexCount(const Polygon& p) {
    return p.points.size();
}

size_t countEven(const std::vector<Polygon>& figures) {
    return std::count_if(figures.cbegin(), figures.cend(), [](const Polygon& p) {
        return getVertexCount(p) % 2 == 0;
        });
}

size_t countOdd(const std::vector<Polygon>& figures) {
    return std::count_if(figures.cbegin(), figures.cend(), [](const Polygon& p) {
        return getVertexCount(p) % 2 != 0;
        });
}

size_t countByVertexCount(const std::vector<Polygon>& figures, size_t vertexCount) {
    return std::count_if(figures.cbegin(), figures.cend(), [vertexCount](const Polygon& p) {
        return getVertexCount(p) == vertexCount;
        });
}

double sumAreaEven(const std::vector<Polygon>& figures) {
    return std::accumulate(figures.cbegin(), figures.cend(), 0.0, [](double sum, const Polygon& p) {
        return sum + (p.points.size() % 2 == 0 ? polygonArea(p) : 0.0);
        });
}

double sumAreaOdd(const std::vector<Polygon>& figures) {
    return std::accumulate(figures.cbegin(), figures.cend(), 0.0, [](double sum, const Polygon& p) {
        return sum + (p.points.size() % 2 == 1 ? polygonArea(p) : 0.0);
        });
}

double sumAreaByVertexCount(const std::vector<Polygon>& figures, size_t vertexCount) {
    return std::accumulate(figures.cbegin(), figures.cend(), 0.0, [vertexCount](double sum, const Polygon& p) {
        return sum + (p.points.size() == vertexCount ? polygonArea(p) : 0.0);
        });
}

double meanArea(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("No figures");
    double total = std::accumulate(figures.cbegin(), figures.cend(), 0.0, [](double sum, const Polygon& p) {
        return sum + polygonArea(p);
        });
    return total / figures.size();
}

double maxArea(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("No figures");
    auto it = std::max_element(figures.cbegin(), figures.cend(), [](const Polygon& a, const Polygon& b) {
        return polygonArea(a) < polygonArea(b);
        });
    return polygonArea(*it);
}

size_t maxVertexCount(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("No figures");
    auto it = std::max_element(figures.cbegin(), figures.cend(), [](const Polygon& a, const Polygon& b) {
        return getVertexCount(a) < getVertexCount(b);
        });
    return getVertexCount(*it);
}

double minArea(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("No figures");
    auto it = std::min_element(figures.cbegin(), figures.cend(), [](const Polygon& a, const Polygon& b) {
        return polygonArea(a) < polygonArea(b);
        });
    return polygonArea(*it);
}

size_t minVertexCount(const std::vector<Polygon>& figures) {
    if (figures.empty()) throw std::runtime_error("No figures");
    auto it = std::min_element(figures.cbegin(), figures.cend(), [](const Polygon& a, const Polygon& b) {
        return getVertexCount(a) < getVertexCount(b);
        });
    return getVertexCount(*it);
}

size_t countRectangles(const std::vector<Polygon>& figures) {
    return std::count_if(figures.cbegin(), figures.cend(), isRectangle);
}

size_t countSameShape(const std::vector<Polygon>& figures, const Polygon& target) {
    return std::count_if(figures.cbegin(), figures.cend(), [&target](const Polygon& p) {
        return isSameShape(p, target);
        });
}
