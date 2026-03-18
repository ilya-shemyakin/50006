#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "circle.h"
#include "composite_shape.h"

void printShape(const Shape& s) {
  Point c = s.getCenter();
  std::cout << std::fixed << std::setprecision(2)
            << "[" << s.getName()
            << ", (" << c.x << ", " << c.y << ")"
            << ", " << s.getArea() << "]\n";
}

int main() {
  std::vector<std::shared_ptr<Shape>> shapes;

  shapes.push_back(std::make_shared<Rectangle>(Point{0, 0}, Point{10, 5}));
  shapes.push_back(std::make_shared<Rectangle>(Point{1, 1}, Point{4,  4}));
  shapes.push_back(std::make_shared<Circle>(Point{3, 3}, 5.0));
  shapes.push_back(std::make_shared<Circle>(Point{0, 0}, 2.0));

  auto comp = std::make_shared<CompositeShape>();
  comp->add(std::make_shared<Rectangle>(Point{0, 0}, Point{6, 4}));
  comp->add(std::make_shared<Circle>(Point{3, 2}, 3.0));
  shapes.push_back(comp);

  std::cout << "=== Before scaling ===\n";
  for (const auto& s : shapes) printShape(*s);

  for (auto& s : shapes) s->scale(2.0);

  std::cout << "\n=== After scaling x2 ===\n";
  for (const auto& s : shapes) printShape(*s);

  return 0;
}