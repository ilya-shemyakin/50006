#include "INFRAME.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include <limits>
#include <stdexcept>

BoundingBox getPolyBoundingBox(const Polygon& p) {
    auto cmpX = [](const Point& a, const Point& b) { return a.x < b.x; };
    auto cmpY = [](const Point& a, const Point& b) { return a.y < b.y; };
    auto minItX = std::min_element(p.points.begin(), p.points.end(), cmpX);
    auto maxItX = std::max_element(p.points.begin(), p.points.end(), cmpX);
    auto minItY = std::min_element(p.points.begin(), p.points.end(), cmpY);
    auto maxItY = std::max_element(p.points.begin(), p.points.end(), cmpY);
    return {minItX->x, maxItX->x, minItY->y, maxItY->y};
}

BoundingBox mergeBoundingBoxes(BoundingBox acc, const Polygon& p) {
    BoundingBox pbb = getPolyBoundingBox(p);
    return {
        std::min(acc.minX_, pbb.minX_),
        std::max(acc.maxX_, pbb.maxX_),
        std::min(acc.minY_, pbb.minY_),
        std::max(acc.maxY_, pbb.maxY_)
    };
}

bool isInsideBoundingBox(const Point& p, const BoundingBox& bb) {
    return p.x >= bb.minX_ && p.x <= bb.maxX_ &&
           p.y >= bb.minY_ && p.y <= bb.maxY_;
}

bool inFrame(const std::vector<Polygon>& polygons, const Polygon& target) {
    if (polygons.empty()) {
        throw std::runtime_error("empty");
    }
    BoundingBox initBB = {
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::lowest(),
        std::numeric_limits<int>::max(),
        std::numeric_limits<int>::lowest()
    };
    BoundingBox bb = std::accumulate(
        polygons.begin(), polygons.end(), initBB, mergeBoundingBoxes);
    auto checkPoint = std::bind(isInsideBoundingBox,
        std::placeholders::_1, std::cref(bb));
    return std::all_of(target.points.begin(), target.points.end(), checkPoint);
}
