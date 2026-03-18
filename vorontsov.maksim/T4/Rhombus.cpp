#include "Rhombus.h"

Rhombus::Rhombus(Point centerPoint, float diagV, float diagH)
    : center(centerPoint), diagonalVertical(diagV), diagonalHorizontal(diagH) {
}

float Rhombus::getArea() const {
    return (diagonalVertical * diagonalHorizontal) / 2.0;
}

Point Rhombus::getCenter() const {
    return center;
}

void Rhombus::move(float x_, float y_) {
    center.x += x_;
    center.y += y_;
}

void Rhombus::scale(float coefficient) {
    diagonalVertical *= coefficient;
    diagonalHorizontal *= coefficient;
}

const char* Rhombus::getName() const {
    return "Rhombus";
}
