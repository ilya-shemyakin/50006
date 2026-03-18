#include "composite_shape.h"

void CompositeShape::add(std::shared_ptr<Shape> shape) {
  shapes_.push_back(shape);
}

double CompositeShape::getArea() const {
  double total = 0.0;
  for (const auto& s : shapes_) total += s->getArea();
  return total;
}

Point CompositeShape::getCenter() const {
  double sx = 0.0, sy = 0.0, totalArea = 0.0;
  for (const auto& s : shapes_) {
    double a = s->getArea();
    Point  c = s->getCenter();
    sx += c.x * a;
    sy += c.y * a;
    totalArea += a;
  }
  return { sx / totalArea, sy / totalArea };
}

void CompositeShape::move(double dx, double dy) {
  for (auto& s : shapes_) s->move(dx, dy);
}

void CompositeShape::scale(double factor) {
  Point c = getCenter();
  for (auto& s : shapes_) {
    Point sc = s->getCenter();
    s->move((sc.x - c.x) * (factor - 1.0),
            (sc.y - c.y) * (factor - 1.0));
    s->scale(factor);
  }
}

std::string CompositeShape::getName() const {
  return "COMPOSITE";
}