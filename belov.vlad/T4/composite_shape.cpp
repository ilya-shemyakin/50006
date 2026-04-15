#include "composite_shape.h"
#include <stdexcept>
#include <limits>
#include <memory>

CompositeShape::CompositeShape() {}

CompositeShape::~CompositeShape() {}

void CompositeShape::addShape(std::unique_ptr<Shape> shape) {
    if (!shape) {
        throw std::invalid_argument("Cannot add null shape composite");
    }
    shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const {
    double totalArea = 0;
    for (const std::unique_ptr<Shape>& shape : shapes) {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const {
    if (shapes.empty()) {
        return Point(0, 0);
    }

    double minX = std::numeric_limits<double>::max();
    double minY = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double maxY = std::numeric_limits<double>::lowest();

    for (const std::unique_ptr<Shape>& shape : shapes) {
        Point center = shape->getCenter();
        minX = std::min(minX, center.x);
        minY = std::min(minY, center.y);
        maxX = std::max(maxX, center.x);
        maxY = std::max(maxY, center.y);
    }

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CompositeShape::move(double dx, double dy) {
    for (std::unique_ptr<Shape>& shape : shapes) {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    if (factor <= 0) {
        throw std::invalid_argument("Scale factor must be positive");
    }

    Point compositeCenter = getCenter();

    for (std::unique_ptr<Shape>& shape : shapes) {
        Point shapeCenter = shape->getCenter();
        double dx = shapeCenter.x - compositeCenter.x;
        double dy = shapeCenter.y - compositeCenter.y;

        shape->move(dx * (factor - 1), dy * (factor - 1));
        shape->scale(factor);
    }
}

const Shape& CompositeShape::getShape(size_t index) const {
    if (index >= shapes.size()) {
        throw std::out_of_range("Index out of range in CompositeShape");
    }
    return *shapes[index];
}

const char* CompositeShape::getName() const {
    return "COMPOSITE";
}

size_t CompositeShape::getSize() const {
    return shapes.size();
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const {
    return shapes;
}
