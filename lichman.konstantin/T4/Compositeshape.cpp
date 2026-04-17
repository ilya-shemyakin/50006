#include "Compositeshape.h"

void CompositeShape::addShape(const std::shared_ptr<Shape>& shape) {
    shapes_.push_back(shape);
}

double CompositeShape::getArea() const {
    double total = 0.0;
    for (const auto& s : shapes_) {
        total += s->getArea();
    }
    return total;
}

Point CompositeShape::getCenter() const {
    Point center{ 0.0, 0.0 };

    if (shapes_.empty())
        return center;

    for (const auto& s : shapes_) {
        Point c = s->getCenter();
        center.x += c.x;
        center.y += c.y;
    }

    center.x /= shapes_.size();
    center.y /= shapes_.size();

    return center;
}

void CompositeShape::move(double dx, double dy) {
    for (auto& s : shapes_) {
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor) {
    Point center = getCenter();

    for (auto& s : shapes_) {
        Point oldCenter = s->getCenter();

        double newX = center.x + (oldCenter.x - center.x) * factor;
        double newY = center.y + (oldCenter.y - center.y) * factor;

        s->move(newX - oldCenter.x, newY - oldCenter.y);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const {
    return "COMPOSITE";
}

#endif
