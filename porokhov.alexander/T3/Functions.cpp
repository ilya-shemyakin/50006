#include "Functions.h"

#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>

using namespace std::placeholders;

int getVertexCount(const Polygon& p) {
    return p.points.size();
}

int countEven(const std::vector<Polygon>& figures) {
    auto comp = std::bind(
        std::equal_to<int>(),
        std::bind(
            std::modulus<int>(), std::bind(getVertexCount, _1), 2),
        0);

    return std::count_if(figures.cbegin(), figures.cend(), comp);
}

int countOdd(const std::vector<Polygon>& figures) {
    auto comp = std::bind(
        std::equal_to<int>(),
        std::bind(
            std::modulus<int>(), std::bind(getVertexCount, _1), 2),
        1);

    return std::count_if(figures.cbegin(), figures.cend(), comp);
}

int countByVertexCount(const std::vector<Polygon>& figures, int vertexCount) {
    auto comp = std::bind(
        std::equal_to<int>(),
        std::bind(getVertexCount, _1),
        vertexCount);

    return std::count_if(figures.cbegin(), figures.cend(), comp);
}

double maxArea(const std::vector<Polygon>& figures) {
    if (figures.empty()) {
        throw std::runtime_error("No figures");
    }
    auto comp = std::bind(std::less<>(), std::bind(area, _1), std::bind(area, _2));
    auto it = std::max_element(figures.cbegin(), figures.cend(), comp);
    return area(*it);
}

int maxVertexCount(const std::vector<Polygon>& figures) {
    if (figures.empty()) {
        throw std::runtime_error("No figures");
    }
    auto comp = std::bind(std::less<>(), std::bind(getVertexCount, _1), std::bind(getVertexCount, _2));
    auto it = std::max_element(figures.cbegin(), figures.cend(), comp);
    return getVertexCount(*it);
}

double minArea(const std::vector<Polygon>& figures) {
    if (figures.empty()) {
        throw std::runtime_error("No figures");
    }
    auto comp = std::bind(std::less<>(), std::bind(area, _1), std::bind(area, _2));
    auto it = std::min_element(figures.cbegin(), figures.cend(), comp);
    return area(*it);
}

int minVertexCount(const std::vector<Polygon>& figures) {
    if (figures.empty()) {
        throw std::runtime_error("No figures");
    }
    auto comp = std::bind(std::less<>(), std::bind(getVertexCount, _1), std::bind(getVertexCount, _2));
    auto it = std::min_element(figures.cbegin(), figures.cend(), comp);
    return getVertexCount(*it);
}

double sumAreaEven(const std::vector<Polygon>& figures) {
    return std::accumulate(figures.cbegin(), figures.cend(), 0.0,
        [](double sum, const Polygon& p) {
            return sum + (p.points.size() % 2 == 0 ? area(p) : 0.0);
        });
}

double sumAreaOdd(const std::vector<Polygon>& figures) {
    return std::accumulate(figures.cbegin(), figures.cend(), 0.0,
        [](double sum, const Polygon& p) {
            return sum + (p.points.size() % 2 == 1 ? area(p) : 0.0);
        });
}

double sumAreaByVertexCount(const std::vector<Polygon>& figures, int vertexCount) {
    return std::accumulate(figures.cbegin(), figures.cend(), 0.0,
        [vertexCount](double sum, const Polygon& p) {
            return sum + (static_cast<int>(p.points.size()) == vertexCount ? area(p) : 0.0);
        });
}

double meanArea(const std::vector<Polygon>& figures) {
    if (figures.empty()) {
        throw std::runtime_error("No figures");
    }
    double total = std::accumulate(figures.cbegin(), figures.cend(), 0.0,
        [](double sum, const Polygon& p) {
            return sum + area(p);
        });
    return total / figures.size();
}

// MAXSEQ - максимальное количество идущих подряд фигур, идентичных target
int maxConsecutiveEqual(const std::vector<Polygon>& figures, const Polygon& target) {
    auto result = std::accumulate(
        figures.cbegin(), figures.cend(),
        std::make_pair(0, 0),
        [&target](std::pair<int, int> acc, const Polygon& p) {
            int current = (p == target) ? acc.second + 1 : 0;
            return std::make_pair(std::max(acc.first, current), current);
        });
    return result.first;
}

// PERMS - количество фигур, являющихся перестановкой вершин target
int countPermutations(const std::vector<Polygon>& figures, const Polygon& target) {
    auto pred = std::bind(isPermutation, _1, std::cref(target));
    return std::count_if(figures.cbegin(), figures.cend(), pred);
}
