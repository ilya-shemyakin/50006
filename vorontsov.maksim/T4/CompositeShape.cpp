#include "Point.h"
#include "CompositeShape.h"
#include <cmath>


CompositeShape::CompositeShape(): shapes(){
}

void CompositeShape::addShape(std::shared_ptr<Shape> shape){
    shapes.push_back(shape);
}

float CompositeShape::getArea()const {
    float totalArea = 0.0;
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

    for (const auto& shape : shapes){
        Point center = shape->getCenter();
        float area = shape->getArea();
        float size = std::sqrt(area);

        minX = std::min(minX, center.x - size);
        minY = std::min(minY, center.y - size);
        maxX = std::max(maxX, center.x + size);
        maxY = std::max(maxY, center.y + size);
    }

    return Point((minX + maxX)/ 2.0, (minY + maxY)/ 2.0);
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

const char* CompositeShape::getName()const {
    return "CompositeShape";
}
