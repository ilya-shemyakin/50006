#include "Functions.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdexcept>

using namespace std::placeholders;

int countRectangles(const std::vector<Polygon>& figures) {
    if (figures.empty()) {
        return 0;
    }

    auto isRect = std::bind(isRectangle, _1);
    return std::count_if(figures.cbegin(), figures.cend(), isRect);
}

int countSameShape(const std::vector<Polygon>& figures, const Polygon& target) {
    if (figures.empty()) {
        return 0;
    }

    auto pred = std::bind(isSameShape, _1, std::cref(target));
    return std::count_if(figures.cbegin(), figures.cend(), pred);
}

