#include "Commands.hpp"
#include "Polygon.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <cmath>
#include <cctype>
#include <vector>
#include <stdexcept>
#include <cstddef>
#include <string>
#include <sstream>


double calculateArea(const Polygon& polygon) {
    double calculatedArea{};

    const std::size_t numberOfPolygonPoints = polygon.points.size();
    if (numberOfPolygonPoints < 3) {
        calculatedArea = 0.0;
        return calculatedArea;
    }

    std::vector<double> contributions(numberOfPolygonPoints - 1);

    std::vector<Point>::const_iterator constBegin = polygon.points.cbegin();
    std::vector<Point>::const_iterator constEnd = polygon.points.cend();

    std::transform(
        constBegin,
        constEnd - 1,
        constBegin + 1,
        contributions.begin(),
        [](const Point& firstPoint, const Point& secondPoint) {
            return static_cast<double>(firstPoint.x) * secondPoint.y - static_cast<double>(secondPoint.x) * firstPoint.y;
        }
    );

    double firstLastPointsContribution = static_cast<double>((constEnd - 1)->x) * constBegin->y - static_cast<double>((constEnd - 1)->y) * constBegin->x;

    double sumOfContributions = std::accumulate(contributions.cbegin(), contributions.cend(), 0.0) + firstLastPointsContribution;
    
    calculatedArea = std::abs(sumOfContributions) / 2.0;
    
    return calculatedArea;  
}


template <typename Predicate>
double calculateSumAreaIf(const std::vector<Polygon>& polygons, Predicate predicate) {
    return std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        0.0,
        [predicate](double sum, const Polygon& polygon) {
            if (predicate(polygon)) {
                sum += calculateArea(polygon);
            }
            return sum;
        }
    );
}

double calculateAreaByNumberOfVertices(const std::vector<Polygon>& polygons, std::size_t numberOfVertexes) {
    return calculateSumAreaIf(
        polygons,
        [numberOfVertexes](const Polygon& polygon) {
            return numberOfVertexes == polygon.points.size();
        }
    );
}

double calculateAreaEven(const std::vector<Polygon>& polygons) {
    return calculateSumAreaIf(
        polygons,
        [](const Polygon& polygon) {
            return (polygon.points.size() % 2) == 0;
        }
    );
}

double calculateAreaOdd(const std::vector<Polygon>& polygons) {
    return calculateSumAreaIf(
        polygons,
        [](const Polygon& polygon) {
            return (polygon.points.size() % 2) != 0;
        }
    );
}

double calculateAreaMean(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::invalid_argument("No polygons for mean area calculation");
    }

    double sumOfAreas = calculateSumAreaIf(
        polygons,
        [](const Polygon&) {
            return true;
        }
    );

    return sumOfAreas / polygons.size();
}

template <typename Comparator>
std::vector<Polygon>::const_iterator findMaxPolygon(const std::vector<Polygon>& polygons, Comparator comparator) {
    if (polygons.empty()) {
        throw std::invalid_argument("No polygons to search for maximum element");
    }

    return std::max_element(
        polygons.cbegin(),
        polygons.cend(),
        comparator
    );
}

template <typename Comparator>
std::vector<Polygon>::const_iterator findMinPolygon(const std::vector<Polygon>& polygons, Comparator comparator) {
    if (polygons.empty()) {
        throw std::invalid_argument("No polygons to search for minimum element");
    }

    return std::min_element(
        polygons.cbegin(),
        polygons.cend(),
        comparator
    );
}

struct AreaComparator {
    bool operator()(const Polygon& first, const Polygon& second) const {
        return calculateArea(first) < calculateArea(second);
    }
};

struct VertexComparator {
    bool operator()(const Polygon& first, const Polygon& second) const {
        return first.points.size() < second.points.size();
    }

};

double calculateMaxArea(const std::vector<Polygon>& polygons) {
    return calculateArea(
        *findMaxPolygon(
                polygons,
                AreaComparator()
            )
    );

    //return calculateArea(*maxElementIterator);
}

double calculateMinArea(const std::vector<Polygon>& polygons) {
    return calculateArea(
        *findMinPolygon(
            polygons,
            AreaComparator()
        )
    );

    //return calculateArea(*minElementIterator);
}

std::size_t calculateMaxVertices(const std::vector<Polygon>& polygons) {
    return findMaxPolygon(polygons, VertexComparator{})->points.size();
}

std::size_t calculateMinVertices(const std::vector<Polygon>& polygons) {
    return findMinPolygon(polygons, VertexComparator{})->points.size();
}


template <typename Predicate>
std::size_t countIf(const std::vector<Polygon>& polygons, Predicate predicate) {
    return std::count_if(
        polygons.cbegin(),
        polygons.cend(),
        predicate
    );
}

std::size_t countEven(const std::vector<Polygon>& polygons) {
    return countIf(
        polygons,
        [](const Polygon& polygon) {
            return (polygon.points.size() % 2) == 0;
        }
    );
}

std::size_t countOdd(const std::vector<Polygon>& polygons) {
    return countIf(
        polygons,
        [](const Polygon& polygon) {
            return (polygon.points.size() % 2) != 0; 
        }
    );
}

std::size_t countByNumberOfVertices(const std::vector<Polygon>& polygons, std::size_t sizeExpected) {
    return countIf(
        polygons,
        [sizeExpected](const Polygon& polygon) {
            return (polygon.points.size() == sizeExpected);
        }
    );
}

//perms

bool isPermutation(const Polygon& first, const Polygon& second) {
    if (first.points.size() != second.points.size()) {
        return false;
    }

    return std::is_permutation(
        first.points.cbegin(),
        first.points.cend(),
        second.points.cbegin(),
        second.points.cend(),
        [](const Point& first, const Point& second) {
            return (first.x == second.x && first.y == second.y);
        } 
    );
}

std::size_t countPermutations(const std::vector<Polygon>& polygons, const Polygon& targetPolygon) {
    return countIf(
        polygons,
        [&targetPolygon](const Polygon& polygon) {
            return isPermutation(polygon, targetPolygon);
        }
    );
}

//inframe

namespace {
    struct Frame {
        int minX;
        int maxX;
        int minY;
        int maxY;

        Frame(const Point& point) : minX(point.x), maxX(point.x), minY(point.y), maxY(point.y) {};
    };
}

Frame addPointToFrame(Frame dest, const Point& newPoint) {
    dest.maxX = std::max(newPoint.x, dest.maxX);
    dest.maxY = std::max(newPoint.y, dest.maxY);
    dest.minX = std::min(newPoint.x, dest.minX);
    dest.minY = std::min(newPoint.y, dest.minY);

    return dest;
}

Frame addPolygonToFrame(Frame frame, const Polygon& polygon) {
    return std::accumulate(
        polygon.points.cbegin(),
        polygon.points.cend(),
        frame,
        [](Frame currentFrame, const Point& point) {
            return addPointToFrame(currentFrame, point);
        }
    );
}

Frame calculateFrame(const std::vector<Polygon>& polygons) {
    if (polygons.empty()) {
        throw std::invalid_argument("No vectors to calculate a frame");
    }

    Frame currentFrame(polygons.front().points.front());

    return std::accumulate(
        polygons.cbegin(),
        polygons.cend(),
        currentFrame,
        [](Frame currentFrame, const Polygon& polygon) {
            return addPolygonToFrame(currentFrame, polygon);
        }
    );

}

bool isPointInFrame(const Frame& frame, const Point& point) {
    return (
        point.x <= frame.maxX &&
        point.y <= frame.maxY &&
        point.x >= frame.minX &&
        point.y >= frame.minY
    );
}

bool isPolygonInFrame(const Frame& frame, const Polygon& polygon) {
    return std::all_of(
        polygon.points.cbegin(),
        polygon.points.cend(),
        [&frame](const Point& point) {
            return isPointInFrame(frame, point);
        }
    );
}

bool checkInFrame(const std::vector<Polygon>& polygons, const Polygon& targetPolygon) {
    return isPolygonInFrame(calculateFrame(polygons), targetPolygon);
}
