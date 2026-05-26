#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

struct Point {
    int x, y;
};

struct Polygon {
    std::vector<Point> points;
};

std::istream& operator>>(std::istream& in, Point& p) {
    char c;
    if (!(in >> c) || c != '(') { in.setstate(std::ios::failbit); return in; }
    if (!(in >> p.x)) { in.setstate(std::ios::failbit); return in; }
    if (!(in >> c) || c != ';') { in.setstate(std::ios::failbit); return in; }
    if (!(in >> p.y)) { in.setstate(std::ios::failbit); return in; }
    if (!(in >> c) || c != ')') { in.setstate(std::ios::failbit); return in; }
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    size_t n = 0;
    if (!(in >> n) || n < 3) { in.setstate(std::ios::failbit); return in; }
    poly.points.resize(n);
    std::copy_n(std::istream_iterator<Point>(in), n, poly.points.begin());
    if (!in) poly.points.clear();
    return in;
}

bool operator==(const Point& a, const Point& b) {
    return a.x == b.x && a.y == b.y;
}

bool operator==(const Polygon& a, const Polygon& b) {
    return a.points == b.points;
}

struct CrossProduct {
    long long operator()(long long acc, const std::pair<const Point*, const Point*>& pp) const {
        return acc + static_cast<long long>(pp.first->x) * pp.second->y
            - static_cast<long long>(pp.second->x) * pp.first->y;
    }
};

double polygonArea(const Polygon& poly) {
    const auto& pts = poly.points;
    size_t n = pts.size();

    std::vector<std::pair<const Point*, const Point*>> edges(n);
    std::transform(pts.begin(), pts.end(), edges.begin(),
        [&pts, &n](const Point& p) -> std::pair<const Point*, const Point*> {
            size_t i = &p - pts.data();
            return { &p, &pts[(i + 1) % n] };
        });

    long long sum = std::accumulate(edges.begin(), edges.end(), 0LL, CrossProduct{});
    return std::abs(sum) / 2.0;
}

void printFixed1(double v) {
    std::ios_base::fmtflags oldFlags = std::cout.flags();
    std::streamsize oldPrecision = std::cout.precision();

    std::cout << std::fixed;
    std::cout.precision(1);
    std::cout << v << "\n";

    std::cout.flags(oldFlags);
    std::cout.precision(oldPrecision);
}

void cmdArea(const std::vector<Polygon>& polys, const std::string& arg) {
    if (arg == "MEAN") {
        if (polys.empty()) { std::cout << "<INVALID COMMAND>\n"; return; }
        std::vector<double> areas(polys.size());
        std::transform(polys.begin(), polys.end(), areas.begin(), polygonArea);
        printFixed1(std::accumulate(areas.begin(), areas.end(), 0.0) / polys.size());
        return;
    }

    if (arg == "EVEN" || arg == "ODD") {
        bool even = (arg == "EVEN");
        std::vector<double> areas(polys.size());
        std::transform(polys.begin(), polys.end(), areas.begin(), [even](const Polygon& p) {
            return (p.points.size() % 2 == 0) == even ? polygonArea(p) : 0.0;
            });
        printFixed1(std::accumulate(areas.begin(), areas.end(), 0.0));
        return;
    }

    size_t n = 0;
    try { n = std::stoul(arg); }
    catch (...) { std::cout << "<INVALID COMMAND>\n"; return; }
    if (n < 3) { std::cout << "<INVALID COMMAND>\n"; return; }

    std::vector<double> areas(polys.size());
    std::transform(polys.begin(), polys.end(), areas.begin(), [n](const Polygon& p) {
        return p.points.size() == n ? polygonArea(p) : 0.0;
        });
    printFixed1(std::accumulate(areas.begin(), areas.end(), 0.0));
}

void cmdMax(const std::vector<Polygon>& polys, const std::string& arg) {
    if (polys.empty()) { std::cout << "<INVALID COMMAND>\n"; return; }
    if (arg == "AREA") {
        auto it = std::max_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) { return polygonArea(a) < polygonArea(b); });
        printFixed1(polygonArea(*it));
    }
    else if (arg == "VERTEXES") {
        auto it = std::max_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); });
        std::cout << it->points.size() << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void cmdMin(const std::vector<Polygon>& polys, const std::string& arg) {
    if (polys.empty()) { std::cout << "<INVALID COMMAND>\n"; return; }
    if (arg == "AREA") {
        auto it = std::min_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) { return polygonArea(a) < polygonArea(b); });
        printFixed1(polygonArea(*it));
    }
    else if (arg == "VERTEXES") {
        auto it = std::min_element(polys.begin(), polys.end(),
            [](const Polygon& a, const Polygon& b) { return a.points.size() < b.points.size(); });
        std::cout << it->points.size() << "\n";
    }
    else {
        std::cout << "<INVALID COMMAND>\n";
    }
}

void cmdCount(const std::vector<Polygon>& polys, const std::string& arg) {
    if (arg == "EVEN") {
        std::cout << std::count_if(polys.begin(), polys.end(),
            [](const Polygon& p) { return p.points.size() % 2 == 0; }) << "\n";
    }
    else if (arg == "ODD") {
        std::cout << std::count_if(polys.begin(), polys.end(),
            [](const Polygon& p) { return p.points.size() % 2 != 0; }) << "\n";
    }
    else {
        size_t n = 0;
        try { n = std::stoul(arg); }
        catch (...) { std::cout << "<INVALID COMMAND>\n"; return; }
        if (n < 3) { std::cout << "<INVALID COMMAND>\n"; return; }
        std::cout << std::count_if(polys.begin(), polys.end(),
            [n](const Polygon& p) { return p.points.size() == n; }) << "\n";
    }
}

Polygon parsePolygon(const std::string& line) {
    std::istringstream ss(line);
    Polygon poly;
    if (!(ss >> poly)) poly.points.clear();
    return poly;
}

void cmdRmecho(std::vector<Polygon>& polys, const Polygon& target) {
    if (target.points.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    std::vector<Polygon> result;
    result.reserve(polys.size());

    size_t removed = 0;

    for (size_t i = 0; i < polys.size(); ) {

        if (polys[i] == target) {
            size_t j = i;

            while (j < polys.size() && polys[j] == target) {
                ++j;
            }

            removed += (j - i);
            i = j;
        }
        else {
            result.push_back(polys[i]);
            ++i;
        }
    }

    polys = std::move(result);

    std::cout << removed << "\n";
}

void cmdInframe(const std::vector<Polygon>& polys, const Polygon& target) {
    if (target.points.empty()) {
        std::cout << "<INVALID COMMAND>\n";
        return;
    }

    if (polys.empty()) {
        std::cout << "<FALSE>\n";
        return;
    }

    auto first = true;

    int minX = 0, maxX = 0;
    int minY = 0, maxY = 0;

    for (const auto& poly : polys) {
        for (const auto& p : poly.points) {

            if (first) {
                minX = maxX = p.x;
                minY = maxY = p.y;
                first = false;
            }
            else {
                minX = std::min(minX, p.x);
                maxX = std::max(maxX, p.x);
                minY = std::min(minY, p.y);
                maxY = std::max(maxY, p.y);
            }
        }
    }

    bool inside = std::all_of(target.points.begin(), target.points.end(),
        [&](const Point& p) {
            return p.x >= minX && p.x <= maxX &&
                p.y >= minY && p.y <= maxY;
        });

    std::cout << (inside ? "<TRUE>" : "<FALSE>") << "\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: no filename provided\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polys;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        Polygon poly;
        if (ss >> poly) {
            std::string leftover;
            if (!(ss >> leftover))
                polys.push_back(std::move(poly));
        }
    }

    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "AREA") {
            std::string arg;
            if (!(std::cin >> arg)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdArea(polys, arg);
        }
        else if (cmd == "MAX") {
            std::string arg;
            if (!(std::cin >> arg)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdMax(polys, arg);
        }
        else if (cmd == "MIN") {
            std::string arg;
            if (!(std::cin >> arg)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdMin(polys, arg);
        }
        else if (cmd == "COUNT") {
            std::string arg;
            if (!(std::cin >> arg)) { std::cout << "<INVALID COMMAND>\n"; continue; }
            cmdCount(polys, arg);
        }
        else if (cmd == "RMECHO") {
            std::string rest;
            std::getline(std::cin, rest);
            if (rest.empty() || rest[0] != ' ') { std::cout << "<INVALID COMMAND>\n"; continue; }
            Polygon target = parsePolygon(rest.substr(1));
            cmdRmecho(polys, target);
        }
        else if (cmd == "INFRAME") {
            std::string rest;
            std::getline(std::cin, rest);
            if (rest.empty() || rest[0] != ' ') { std::cout << "<INVALID COMMAND>\n"; continue; }
            Polygon target = parsePolygon(rest.substr(1));
            cmdInframe(polys, target);
        }
        else {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    return 0;
}