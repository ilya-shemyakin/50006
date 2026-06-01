#include "Structs.h"
#include "Operators.h"
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <stdexcept>
Polygon parsePolygon(const std::string& string) {
    size_t spaceCount = std::count(string.begin(), string.end(), ' ');
    std::istringstream iss(string);
    Polygon polygon{};
    iss >> polygon;
    if (iss.fail()) {
        throw std::runtime_error("invalid format");
    }
    if (spaceCount != polygon.points.size()) {
        throw std::runtime_error("invalid spaces");
    }
    char leftover{};
    if (iss >> leftover) {
        throw std::runtime_error("extra characters");
    }
    return polygon;
}
