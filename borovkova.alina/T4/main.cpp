#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

#include "shape.h"
#include "rectangle.h"
#include "square.h"
#include "compositeShape.h"

void printSimpleShape(const Shape& shape)
{
    Point center = shape.getCenter();

    std::cout
        << shape.getName()
        << ", ("
        << center.x
        << ", "
        << center.y
        << "), "
        << shape.getArea();
}

void printShape(const Shape& shape)
{
    if (const CompositeShape* composite =
        dynamic_cast<const CompositeShape*>(&shape))
    {
        Point center =
            composite->getCenter();

        std::cout
            << "[COMPOSITE, ("
            << center.x
            << ", "
            << center.y
            << "), "
            << composite->getArea()
            << ":\n";

        for (const auto& child :
            composite->getShapes())
        {
            std::cout << "  ";

            printSimpleShape(*child);

            std::cout << '\n';
        }

        std::cout << "]\n";
    }
    else
    {
        std::cout << "[";

        printSimpleShape(shape);

        std::cout << "]\n";
    }
}

int main()
{
    std::cout
        << std::fixed
        << std::setprecision(2);

    std::vector<std::unique_ptr<Shape>>
        shapes;

    shapes.push_back(
        std::make_unique<Rectangle>(
            Point{ 0.0, 0.0 },
            Point{ 4.0, 3.0 }
        )
    );

    shapes.push_back(
        std::make_unique<Rectangle>(
            Point{ -2.0, -1.0 },
            Point{ 1.0, 2.0 }
        )
    );

    shapes.push_back(
        std::make_unique<Square>(
            Point{ 2.0, 2.0 },
            3.0
        )
    );

    shapes.push_back(
        std::make_unique<Square>(
            Point{ -3.0, 1.0 },
            4.0
        )
    );

    auto composite =
        std::make_unique<CompositeShape>();

    composite->addShape(
        std::make_unique<Rectangle>(
            Point{ 1.0, 1.0 },
            Point{ 3.0, 4.0 }
        )
    );

    composite->addShape(
        std::make_unique<Square>(
            Point{ 5.0, 2.0 },
            2.0
        )
    );

    shapes.push_back(
        std::move(composite)
    );

    std::cout << "Before scaling:\n";

    for (const auto& shape : shapes)
    {
        printShape(*shape);
    }

    std::cout << "\nAfter scaling:\n";

    for (auto& shape : shapes)
    {
        shape->scale(2.0);

        printShape(*shape);
    }

    return 0;
}
