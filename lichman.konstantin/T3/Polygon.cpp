#include "Polygon.h"
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator<(const Point& other) const {
    return x < other.x || (x == other.x && y < other.y);
}

bool Polygon::operator==(const Polygon& other) const {
    return points == other.points;
}

std::istream& operator>>(std::istream& is, Point& p) {
    char open = 0, sep = 0, close = 0;
    if (is >> open >> p.x >> sep >> p.y >> close) {
        if (open != '(' || sep != ';' || close != ')') {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    size_t n = 0;
    if (!(in >> n) || n < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }
    poly.points.resize(n);
    std::copy_n(std::istream_iterator<Point>(in), n, poly.points.begin());
    if (!in) {
        poly.points.clear();
    }
    return in;
}

Polygon parsePolygon(const std::string& str) {
    std::istringstream iss(str);
    Polygon p;
    if (!(iss >> p)) throw std::runtime_error("Invalid polygon format");
    std::string leftover;
    if (iss >> leftover) throw std::runtime_error("Extra characters");
    return p;
}

struct AreaAccumulator {
    const std::vector<Point>& points;
    double operator()(double acc, const Point& curr) const {
        size_t idx = &curr - &points[0];
        size_t next_idx = (idx + 1) % points.size();
        return acc + (static_cast<double>(points[idx].x) * points[next_idx].y)
            - (static_cast<double>(points[idx].y) * points[next_idx].x);
    }
};

double polygonArea(const Polygon& p) {
    if (p.points.size() < 3) return 0.0;
    double total_sum = std::accumulate(p.points.begin(), p.points.end(), 0.0, AreaAccumulator{ p.points });
    return std::abs(total_sum) / 2.0;
}

int distSq(const Point& a, const Point& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return dx * dx + dy * dy;
}

bool isRectangle(const Polygon& p) {
    if (p.points.size() != 4) return false;
    int side0 = distSq(p.points[0], p.points[1]);
    int side1 = distSq(p.points[1], p.points[2]);
    int side2 = distSq(p.points[2], p.points[3]);
    int side3 = distSq(p.points[3], p.points[0]);

    if (side0 != side2 || side1 != side3) return false;

    int diag1 = distSq(p.points[0], p.points[2]);
    int diag2 = distSq(p.points[1], p.points[3]);
    return diag1 == diag2;
}

Polygon normalizeByMinPoint(const Polygon& p) {
    if (p.points.empty()) return p;

    auto minIt = std::min_element(p.points.begin(), p.points.end());
    Point minPt = *minIt;

    Polygon result;
    result.points.resize(p.points.size());
    std::transform(p.points.begin(), p.points.end(), result.points.begin(), [&minPt](const Point& pt) {
        return Point{ pt.x - minPt.x, pt.y - minPt.y };
        });
    return result;
}

bool isSameShape(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) return false;

    Polygon normA = normalizeByMinPoint(a);
    Polygon normB = normalizeByMinPoint(b);

    std::sort(normA.points.begin(), normA.points.end());
    std::sort(normB.points.begin(), normB.points.end());

    return normA == normB;
}
