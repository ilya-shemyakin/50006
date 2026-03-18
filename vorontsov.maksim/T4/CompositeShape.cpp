#include "Point.h"
#include "CompositeShape.h"
#include <cmath>
#include <limits>
#include <stdexcept>
#include <algorithm>


CompositeShape::CompositeShape(): shapes(){
}

void CompositeShape::addShape(std::unique_ptr<Shape> shape){
    if (!shape) {
        throw std::invalid_argument("Cannot add null shape to composite");
    }
    shapes.push_back(std::move(shape));
}

float CompositeShape::getArea()const {
    float totalArea = 0;
    for (const auto& shape : shapes){
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter()const {
    if (shapes.empty()){
        return Point(0, 0);
    }

    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();
    for (const auto& shape : shapes)
    {
        Point center = shape->getCenter();
        minX = std::min(minX, center.x);
        minY = std::min(minY, center.y);
        maxX = std::max(maxX, center.x);
        maxY = std::max(maxY, center.y);
    }
    return Point((minX + maxX) / 2, (minY + maxY) / 2);
}

void CompositeShape::move(float dx, float dy){
    for (auto& shape : shapes){
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(float coefficient){
    Point compositeCenter = getCenter();

    for (auto& shape : shapes){
        Point shapeCenter = shape->getCenter();

        float dx = (shapeCenter.x - compositeCenter.x)* coefficient;
        float dy = (shapeCenter.y - compositeCenter.y)* coefficient;

        shape->move(dx, dy);
        shape->scale(coefficient);
    }
}

const Shape& CompositeShape::getShape(size_t index) const {
    if (index >= shapes.size()) {
        throw std::out_of_range("Index out of range in CompositeShape");
    }
    return *shapes[index];
}

const char* CompositeShape::getName()const {
    return "CompositeShape";
}
