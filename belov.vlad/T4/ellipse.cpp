#include "ellipse.h"
#include <cmath>
#include <stdexcept>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Ellipse::Ellipse(const Point& c, double rx, double ry) : center(c), radiusX(rx), radiusY(ry) {
    if (rx <= 0 || ry <= 0) {
        throw std::invalid_argument("Ellipse radius must be positive");
    }
}

Ellipse::~Ellipse() {}

double Ellipse::getArea() const {
    return M_PI * radiusX * radiusY;
}

Point Ellipse::getCenter() const {
    return center;
}

void Ellipse::move(double dx, double dy) {
    center.x += dx;
    center.y += dy;
}

void Ellipse::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }
    radiusX *= factor;
    radiusY *= factor;
}

const char* Ellipse::getName() const {
    return "ELLIPSE";
}
