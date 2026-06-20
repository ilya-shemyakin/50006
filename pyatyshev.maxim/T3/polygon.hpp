#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <functional>
#include <cctype>
#include <limits>
#include <string>

struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};

inline std::istream& operator>>(std::istream& is, Point& p) {
    char c1, c2, c3;
    is >> c1 >> p.x >> c2 >> p.y >> c3;
    if (c1 != '(' || c2 != ';' || c3 != ')') {
        is.setstate(std::ios::failbit);
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << '(' << p.x << ';' << p.y << ')';
    return os;
}

struct Polygon {
    std::vector<Point> points;

    size_t vertexCount() const {
        return points.size();
    }

    double area() const {
        if (points.size() < 3) return 0.0;

        double sum = 0.0;
        for (size_t i = 0; i < points.size(); ++i) {
            const Point& p1 = points[i];
            const Point& p2 = points[(i + 1) % points.size()];
            sum += static_cast<double>(p1.x * p2.y - p2.x * p1.y);
        }
        return std::fabs(sum) / 2.0;
    }

    bool isRectangle() const {
        if (points.size() != 4) return false;

        auto dot = [](const Point& a, const Point& b) {
            return a.x * b.x + a.y * b.y;
        };

        auto sub = [](const Point& a, const Point& b) {
            return Point{a.x - b.x, a.y - b.y};
        };

        const Point& p0 = points[0];
        const Point& p1 = points[1];
        const Point& p2 = points[2];
        const Point& p3 = points[3];

        Point v1 = sub(p1, p0);
        Point v2 = sub(p2, p1);
        Point v3 = sub(p3, p2);
        Point v4 = sub(p0, p3);

        return dot(v1, v2) == 0 && dot(v2, v3) == 0 &&
               dot(v3, v4) == 0 && dot(v4, v1) == 0;
    }

    bool isSame(const Polygon& other) const {
        if (points.size() != other.points.size()) return false;

        std::vector<Point> sorted1 = points;
        std::vector<Point> sorted2 = other.points;

        auto comp = [](const Point& a, const Point& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.y < b.y;
        };

        std::sort(sorted1.begin(), sorted1.end(), comp);
        std::sort(sorted2.begin(), sorted2.end(), comp);

        return std::equal(sorted1.begin(), sorted1.end(),
                          sorted2.begin(), sorted2.end());
    }

    bool operator==(const Polygon& other) const {
        if (points.size() != other.points.size()) return false;
        return std::equal(points.begin(), points.end(),
                          other.points.begin(), other.points.end());
    }

    bool operator!=(const Polygon& other) const {
        return !(*this == other);
    }
};

inline std::istream& operator>>(std::istream& is, Polygon& poly) {
    size_t n;
    if (!(is >> n)) return is;

    std::vector<Point> points;
    points.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        Point p;
        if (!(is >> p)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        points.push_back(p);
    }

    if (points.size() == n) {
        poly.points = std::move(points);
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Polygon& poly) {
    os << poly.points.size();
    for (const auto& p : poly.points) {
        os << ' ' << p;
    }
    return os;
}

using Polygons = std::vector<Polygon>;

// Вспомогательные функции для команд
inline bool isValidDigit(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

inline Polygon parsePolygon(const std::string& str) {
    std::istringstream iss(str);
    Polygon p;
    iss >> p;
    return p;
}

inline double areaSum(const Polygons& polygons, bool even) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [even](double sum, const Polygon& p) {
            if ((p.vertexCount() % 2 == 0) == even) {
                return sum + p.area();
            }
            return sum;
        });
}

inline double areaMean(const Polygons& polygons) {
    if (polygons.empty()) return 0.0;
    double sum = std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [](double s, const Polygon& p) { return s + p.area(); });
    return sum / polygons.size();
}

inline double areaByVertexCount(const Polygons& polygons, size_t vertexCount) {
    return std::accumulate(polygons.begin(), polygons.end(), 0.0,
        [vertexCount](double sum, const Polygon& p) {
            if (p.vertexCount() == vertexCount) {
                return sum + p.area();
            }
            return sum;
        });
}

inline double maxArea(const Polygons& polygons) {
    auto it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.area() < b.area();
        });
    return it != polygons.end() ? it->area() : 0.0;
}

inline size_t maxVertexCount(const Polygons& polygons) {
    auto it = std::max_element(polygons.begin(), polygons.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.vertexCount() < b.vertexCount();
        });
    return it != polygons.end() ? it->vertexCount() : 0;
}

inline double minArea(const Polygons& polygons) {
    auto it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.area() < b.area();
        });
    return it != polygons.end() ? it->area() : 0.0;
}

inline size_t minVertexCount(const Polygons& polygons) {
    auto it = std::min_element(polygons.begin(), polygons.end(),
        [](const Polygon& a, const Polygon& b) {
            return a.vertexCount() < b.vertexCount();
        });
    return it != polygons.end() ? it->vertexCount() : 0;
}

inline size_t countByVertexCount(const Polygons& polygons, size_t vertexCount) {
    return std::count_if(polygons.begin(), polygons.end(),
        [vertexCount](const Polygon& p) {
            return p.vertexCount() == vertexCount;
        });
}

inline size_t countEven(const Polygons& polygons) {
    return std::count_if(polygons.begin(), polygons.end(),
        [](const Polygon& p) {
            return p.vertexCount() % 2 == 0;
        });
}

inline size_t countOdd(const Polygons& polygons) {
    return std::count_if(polygons.begin(), polygons.end(),
        [](const Polygon& p) {
            return p.vertexCount() % 2 == 1;
        });
}

inline size_t rectsCount(const Polygons& polygons) {
    return std::count_if(polygons.begin(), polygons.end(),
        std::mem_fn(&Polygon::isRectangle));
}

inline size_t sameCount(const Polygons& polygons, const Polygon& target) {
    return std::count_if(polygons.begin(), polygons.end(),
        [&target](const Polygon& p) {
            return p.isSame(target);
        });
}

#endif
