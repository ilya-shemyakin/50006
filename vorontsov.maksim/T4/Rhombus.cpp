#include "Point.h"
#include "Rhombus.h"
#include <stdexcept>

Rhombus::Rhombus(const Point& centerPoint, float diagV, float diagH)
    : center(centerPoint), diagonalVertical(diagV), diagonalHorizontal(diagH)
{
    if (diagV <= 0 || diagH <= 0) {
        throw std::invalid_argument("Rhombus diagonals must be positive");
    }
}

float Rhombus::getArea()const {
    return (diagonalVertical * diagonalHorizontal)/ 2;
}

Point Rhombus::getCenter()const {
    return center;
}

void Rhombus::move(float x_, float y_){
    center.x += x_;
    center.y += y_;
}

void Rhombus::scale(float coefficient){
    diagonalVertical *= coefficient;
    diagonalHorizontal *= coefficient;
}

const char* Rhombus::getName()const {
    return "Rhombus";
}
