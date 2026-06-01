#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

const size_t MIN_VERTICES = 3;

class StreamGuard {
public:
    explicit StreamGuard(std::ios& stream)
        : stream_(stream), flags_(stream.flags()) {
    }
    ~StreamGuard() {
        stream_.flags(flags_);
    }
private:
    std::ios& stream_;
    std::ios::fmtflags flags_;
};
struct Point {
    int x;
    int y;
};
struct Polygon {
    std::vector<Point> points;
};

struct EchoAccumulator {
    std::vector<Polygon>* result_;
    int count_;
    Polygon target_;
};
struct BoundingBox {
    int minX_;
    int maxX_;
    int minY_;
    int maxY_;
};
Polygon parsePolygon(const std::string& string);
