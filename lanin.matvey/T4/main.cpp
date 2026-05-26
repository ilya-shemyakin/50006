#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "ring.h"
#include "composite_shape.h"

void printShape(const Shape& shape)
{
    Point center = shape.getCenter();
    std::cout << "[" << shape.getName() << ", ("
              << std::fixed << std::setprecision(2) << center.x
              << ", " << std::setprecision(2) << center.y << "), "
              << std::setprecision(2) << shape.getArea() << "]";
}

void printComposite(const CompositeShape& composite)
{
    Point center = composite.getCenter();
    std::cout << "[" << composite.getName() << ", ("
              << std::fixed << std::setprecision(2) << center.x
              << ", " << std::setprecision(2) << center.y << "), "
              << std::setprecision(2) << composite.getArea() << ":\n";

    const auto& shapes = composite.getShapes();
    for (size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout << "  ";
        printShape(*shapes[i]);
        if (i < shapes.size() - 1)
            std::cout << ",";
        std::cout << "\n";
    }
    std::cout << "]";
}

int main()
{
    try
    {
        std::vector<std::unique_ptr<Shape>> shapes;

        // 1. Прямоугольник
        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));

        // 2. Кольцо
        shapes.push_back(std::make_unique<Ring>(Point(2, 2), 5.0, 2.0));

        // 3. Ещё одно кольцо
        shapes.push_back(std::make_unique<Ring>(Point(-3, -1), 3.0, 1.0));

        // 4. Составная фигура, содержащая прямоугольник и кольцо
        auto composite1 = std::make_unique<CompositeShape>();
        composite1->addShape(std::make_unique<Rectangle>(Point(5, 5), Point(7, 8)));
        composite1->addShape(std::make_unique<Ring>(Point(6, 6), 2.0, 0.5));
        shapes.push_back(std::move(composite1));

        // 5. Вторая составная фигура, содержащая только кольцо (но для разнообразия)
        auto composite2 = std::make_unique<CompositeShape>();
        composite2->addShape(std::make_unique<Ring>(Point(-5, -2), 4.0, 1.5));
        shapes.push_back(std::move(composite2));

        // Вывод до масштабирования
        std::cout << "BEFORE SCALE:\n";
        for (const auto& shape : shapes)
        {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite)
                printComposite(*composite);
            else
                printShape(*shape);
            std::cout << "\n";
        }

        // Масштабируем все фигуры в 2 раза
        for (auto& shape : shapes)
            shape->scale(2.0);

        std::cout << "==========================================\n";
        std::cout << "AFTER SCALE:\n";
        for (const auto& shape : shapes)
        {
            const CompositeShape* composite = dynamic_cast<const CompositeShape*>(shape.get());
            if (composite)
                printComposite(*composite);
            else
                printShape(*shape);
            std::cout << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}
