#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>

#include "rectangle.h"
#include "circle.h"
#include "compositeshape.h"

void printShape(const std::shared_ptr<Shape>& shape) {
    if (shape->getName() == "COMPOSITE")
        return;

    Point c = shape->getCenter();

    std::cout << "[" << shape->getName() << ", ("
        << c.x << ", " << c.y << "), "
        << shape->getArea() << "]" << std::endl;
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    std::vector<std::shared_ptr<Shape>> shapes;

    auto r1 = std::make_shared<Rectangle>(Point{ 0.0, 0.0 }, Point{ 4.0, 2.0 });
    auto r2 = std::make_shared<Rectangle>(Point{ 1.0, 1.0 }, Point{ 3.0, 5.0 });
    auto c1 = std::make_shared<Circle>(Point{ 2.0, 2.0 }, 1.0);
    auto c2 = std::make_shared<Circle>(Point{ 5.0, 5.0 }, 2.0);

    auto comp = std::make_shared<CompositeShape>();
    comp->addShape(r1);
    comp->addShape(c1);

    shapes.push_back(r1);
    shapes.push_back(r2);
    shapes.push_back(c1);
    shapes.push_back(c2);
    shapes.push_back(comp);

    std::cout << "Before scaling:\n";
    for (const auto& shape : shapes) {
        printShape(shape);
    }

    for (auto& shape : shapes) {
        shape->scale(2.0);
    }

    std::cout << "\nAfter scaling:\n";
    for (const auto& shape : shapes) {
        printShape(shape);
    }

    return 0;
}