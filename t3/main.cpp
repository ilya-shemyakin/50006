#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <sstream>
#include <cmath>
#include <cctype>

struct Point {
    int x, y;
};

struct Polygon {
    std::vector<Point> points;
};

double polygonArea(const Polygon& poly) {
    double area = 0.0;
    size_t n = poly.points.size();
    for (size_t i = 0; i < n; ++i) {
        const Point& p1 = poly.points[i];
        const Point& p2 = poly.points[(i + 1) % n];
        area += (p1.x * p2.y - p2.x * p1.y);
    }
    return std::abs(area) / 2.0;
}

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator==(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) return false;
    return std::equal(a.points.begin(), a.points.end(), b.points.begin());
}

bool isSameShape(const Polygon& a, const Polygon& b) {
    if (a.points.size() != b.points.size()) return false;
    size_t n = a.points.size();
    for (size_t shift = 0; shift < n; ++shift) {
        bool match = true;
        for (size_t i = 0; i < n; ++i) {
            if (!(a.points[i] == b.points[(i + shift) % n])) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

std::istream& operator>>(std::istream& in, Point& p) {
    char c1, c2, c3;
    in >> c1 >> p.x >> c2 >> p.y >> c3;
    if (c1 != '(' || c2 != ';' || c3 != ')\) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    int vertexCount;
    if (!(in >> vertexCount)) return in;
    std::vector<Point> points;
    for (int i = 0; i < vertexCount; ++i) {
        Point p;
        if (!(in >> p)) {
            in.setstate(std::ios::failbit);
            return in;
        }
        points.push_back(p);
    }
    poly.points = points;
    return in;
}

std::vector<Polygon> readPolygons(const std::string& filename) {
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    if (!file.is_open()) return polygons;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        Polygon poly;
        if (iss >> poly) {
            polygons.push_back(poly);
        }
    }
    return polygons;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: filename required" << std::endl;
        return 1;
    }
    std::vector<Polygon> polygons = readPolygons(argv[1]);
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd == "LESSAREA") {
            Polygon target;
            if (!(iss >> target)) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            double targetArea = polygonArea(target);
            auto lessThanTarget = std::bind(std::less<double>(), std::bind(polygonArea, std::placeholders::_1), targetArea);
            int count = std::count_if(polygons.begin(), polygons.end(), lessThanTarget);
            std::cout << count << std::endl;
        } else if (cmd == "SAME") {
            Polygon target;
            if (!(iss >> target)) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            auto sameAsTarget = std::bind(isSameShape, std::placeholders::_1, std::cref(target));
            int count = std::count_if(polygons.begin(), polygons.end(), sameAsTarget);
            std::cout << count << std::endl;
        } else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
    return 0;
}
