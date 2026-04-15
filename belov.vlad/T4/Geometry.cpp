#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "ellipse.h"
#include "composite_shape.h"

void printShapeInfo(const Shape& shape) {
    Point center = shape.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << shape.getName() << ", (" << center.x << ", " << center.y
        << "), " << shape.getArea();
}

void printComposite(const CompositeShape& composite) {
    Point center = composite.getCenter();
    std::cout << std::fixed << std::setprecision(2);
    std::cout << composite.getName() << ", (" << center.x << ", " << center.y
        << "), " << composite.getArea() << ":\n";

    for (size_t i = 0; i < composite.getSize(); ++i) {
        std::cout << "  ";
        printShapeInfo(composite.getShape(i));
        if (i < composite.getSize() - 1) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "]";
}

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;

        // Обычные фигуры
        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
        shapes.push_back(std::make_unique<Rectangle>(Point(2, 2), Point(6, 5)));
        shapes.push_back(std::make_unique<Ellipse>(Point(1, 1), 2.0, 1.5));
        shapes.push_back(std::make_unique<Ellipse>(Point(-1, -1), 1.5, 2.0));

        // Составная фигура
        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point(-2, -1), Point(0, 1)));
        composite->addShape(std::make_unique<Ellipse>(Point(1, 1), 1.0, 0.8));
        composite->addShape(std::make_unique<Rectangle>(Point(0.5, -0.5), Point(2.5, 1.5)));
        shapes.push_back(std::move(composite));

        std::cout << "=== SHAPES BEFORE SCALING ===\n";
        for (const auto& shape : shapes) {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite) {
                std::cout << "[";
                printComposite(*composite);
                std::cout << "]\n";
            }
            else {
                std::cout << "[";
                printShapeInfo(*shape);
                std::cout << "]\n";
            }
        }

        // Масштабирование
        for (auto& shape : shapes) {
            shape->scale(2.0);
        }

        std::cout << "\nSHAPES AFTER SCALING\n";
        for (const auto& shape : shapes) {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite) {
                std::cout << "[";
                printComposite(*composite);
                std::cout << "]\n";
            }
            else {
                std::cout << "[";
                printShapeInfo(*shape);
                std::cout << "]\n";
            }
        }

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
