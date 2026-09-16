#include "methods.h"

#include <algorithm>
#include <cmath>
#include <functional>
#include <istream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct PolygonLine {
    Polygon polygon;
    bool valid = false;
};

std::istream& operator>>(std::istream& in, PolygonLine& dest) {
    std::istream::sentry guard(in, true);
    dest.valid = false;

    if (guard) {
        std::string line;
        if (std::getline(in, line)) {
            std::istringstream lineIn(line);
            lineIn >> std::noskipws;

            Polygon temp;
            lineIn >> temp;
            if (lineIn && lineIn.peek() == std::char_traits<char>::eof()) {
                dest.valid = true;
                dest.polygon = temp;
            }
        }
    }
    return in;
}

std::vector<Polygon> readPolygons(std::istream& in) {
    std::vector<PolygonLine> lines;
    std::copy_if(
        std::istream_iterator<PolygonLine>(in),
        std::istream_iterator<PolygonLine>(),
        std::back_inserter(lines),
        std::bind(&PolygonLine::valid, std::placeholders::_1)
    );

    std::vector<Polygon> polygons;
    std::transform(
        lines.cbegin(),
        lines.cend(),
        std::back_inserter(polygons),
        std::bind(&PolygonLine::polygon, std::placeholders::_1)
    );
    return polygons;
}

struct AreaAccumulator {
    long long sum;
    Point previous;
};

struct AreaCalculator {
    AreaAccumulator operator()(
        AreaAccumulator accumulator,
        const Point& current
    ) const {
        accumulator.sum +=
            static_cast<long long>(accumulator.previous.x) * current.y -
            static_cast<long long>(current.x) * accumulator.previous.y;
        accumulator.previous = current;
        return accumulator;
    }
};

double getArea(const Polygon& polygon) {
    const Point& first = polygon.points.front();
    AreaAccumulator result = std::accumulate(
        std::next(polygon.points.cbegin()),
        polygon.points.cend(),
        AreaAccumulator{0, first},
        AreaCalculator{}
    );

    result.sum +=
        static_cast<long long>(result.previous.x) * first.y -
        static_cast<long long>(first.x) * result.previous.y;
    return std::abs(result.sum) / 2.0;
}

struct AreaSumByParity {
    std::size_t parity;

    double operator()(double sum, const Polygon& polygon) const {
        if (polygon.points.size() % 2 == parity) {
            return sum + getArea(polygon);
        }
        return sum;
    }
};

double getAreaByParity(
    const std::vector<Polygon>& polygons,
    std::size_t parity
) {
    return std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        0.0,
        AreaSumByParity{parity}
    );
}

struct AreaSum {
    double operator()(double sum, const Polygon& polygon) const {
        return sum + getArea(polygon);
    }
};

double getAreaSum(const std::vector<Polygon>& polygons) {
    return std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        0.0,
        AreaSum{}
    );
}

struct AreaSumByVertexCount {
    std::size_t count;

    double operator()(double sum, const Polygon& polygon) const {
        if (polygon.points.size() == count) {
            return sum + getArea(polygon);
        }
        return sum;
    }
};

double getAreaByVertexCount(
    const std::vector<Polygon>& polygons,
    std::size_t count
) {
    return std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        0.0,
        AreaSumByVertexCount{count}
    );
}

double getMeanArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::logic_error("No polygons");
    }
    return getAreaSum(polygons) / polygons.size();
}

struct CompareArea {
    bool operator()(const Polygon& lhs, const Polygon& rhs) const {
        return getArea(lhs) < getArea(rhs);
    }
};

double getMaxArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::logic_error("No polygons");
    }
    const auto it = std::max_element(
        polygons.cbegin(),
        polygons.cend(),
        CompareArea{}
    );
    return getArea(*it);
}

double getMinArea(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::logic_error("No polygons");
    }
    const auto it = std::min_element(
        polygons.cbegin(),
        polygons.cend(),
        CompareArea{}
    );
    return getArea(*it);
}

struct CompareVertexCount {
    bool operator()(const Polygon& lhs, const Polygon& rhs) const {
        return lhs.points.size() < rhs.points.size();
    }
};

std::size_t getMaxVertexCount(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::logic_error("No polygons");
    }
    const auto it = std::max_element(
        polygons.cbegin(),
        polygons.cend(),
        CompareVertexCount{}
    );
    return it->points.size();
}

std::size_t getMinVertexCount(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::logic_error("No polygons");
    }
    const auto it = std::min_element(
        polygons.cbegin(),
        polygons.cend(),
        CompareVertexCount{}
    );
    return it->points.size();
}

struct VertexCountParity {
    std::size_t parity;

    bool operator()(const Polygon& polygon) const {
        return polygon.points.size() % 2 == parity;
    }
};

std::size_t countByParity(
    const std::vector<Polygon>& polygons,
    std::size_t parity
) {
    return std::count_if(
        polygons.cbegin(),
        polygons.cend(),
        VertexCountParity{parity}
    );
}

struct HasVertexCount {
    std::size_t count;

    bool operator()(const Polygon& polygon) const {
        return polygon.points.size() == count;
    }
};

std::size_t countByVertexCount(
    const std::vector<Polygon>& polygons,
    std::size_t count
) {
    return std::count_if(
        polygons.cbegin(),
        polygons.cend(),
        HasVertexCount{count}
    );
}

struct EchoAccumulator {
    const Polygon& target;
    std::size_t& added;

    std::vector<Polygon> operator()(
        std::vector<Polygon> acc,
        const Polygon& polygon
    ) const {
        acc.push_back(polygon);
        if (polygon == target) {
            acc.push_back(polygon);
            ++added;
        }
        return acc;
    }
};

std::size_t echoPolygon(
    std::vector<Polygon>& polygons,
    const Polygon& target
) {
    std::size_t added = 0;
    polygons = std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        std::vector<Polygon>{},
        EchoAccumulator{target, added}
    );
    return added;
}

struct MaxSeqFunctor {
    const Polygon& target;

    std::pair<std::size_t, std::size_t> operator()(
        std::pair<std::size_t, std::size_t> state,
        const Polygon& polygon
    ) const {
        if (polygon == target) {
            ++state.first;
            state.second = std::max(state.second, state.first);
        } else {
            state.first = 0;
        }
        return state;
    }
};

std::size_t maxSeq(
    const std::vector<Polygon>& polygons,
    const Polygon& target
) {
    const auto result = std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        std::make_pair<std::size_t, std::size_t>(0, 0),
        MaxSeqFunctor{target}
    );
    return result.second;
}
