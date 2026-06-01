#include "Polygon.hpp"
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <sstream>
#include <fstream>
#include <cmath>
#include <functional>

double area(const Polygon& p) {
    const auto& pts = p.points;
    const size_t n = pts.size();
    if (n < 3) {
        return 0.0;
    }

    double sum = 0;
    for (size_t i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        sum += pts[i].x * pts[j].y;
        sum -= pts[i].y * pts[j].x;
    }

    return std::abs(sum) / 2.0;
}

bool operator==(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) {
        return false;
    }
    return std::equal(a.points.begin(), a.points.end(),
        b.points.begin(),
        [](const Point& p1, const Point& p2) {
            return p1.x == p2.x && p1.y == p2.y;
        });
}

Polygon parsePolygon(const std::string& str) {
    std::istringstream iss(str);
    int n;
    iss >> n;
    if (iss.fail()) throw std::runtime_error("Invalid format");
    if (n < 3) throw std::runtime_error("Polygon must have at least 3 vertices");

    Polygon p;
    for (int i = 0; i < n; ++i) {
        char open, sep, close;
        int x, y;
        iss >> open >> x >> sep >> y >> close;
        if (iss.fail() || open != '(' || sep != ';' || close != ')') {
            throw std::runtime_error("Invalid vertex");
        }
        p.points.push_back(Point{ x, y });
    }

    char leftover;
    if (iss >> leftover) {
        throw std::runtime_error("Extra characters after polygon");
    }

    return p;
}

std::vector<Polygon> readShapesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<Polygon> result;
    std::string line;
    while (std::getline(file, line)) {
        try {
            result.push_back(parsePolygon(line));
        }
        catch (...) {}
    }

    return result;
}


bool isRectangle(const Polygon& p) {
    if (p.points.size() != 4) return false;


    auto distSq = [](const Point& a, const Point& b) {
        int dx = a.x - b.x;
        int dy = a.y - b.y;
        return dx*dx + dy*dy;
    };

    std::vector<int> sides;
    for (int i = 0; i < 4; ++i) {
        sides.push_back(distSq(p.points[i], p.points[(i+1)%4]));
    }


    return (sides[0] == sides[2]) && (sides[1] == sides[3]);
}


Polygon normalizeByMinPoint(const Polygon& p) {
    if (p.points.empty()) return p;


    Point minPt = p.points[0];
    for (const auto& pt : p.points) {
        if (pt.x < minPt.x || (pt.x == minPt.x && pt.y < minPt.y)) {
            minPt = pt;
        }
    }


    Polygon result;
    for (const auto& pt : p.points) {
        result.points.push_back({pt.x - minPt.x, pt.y - minPt.y});
    }

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

