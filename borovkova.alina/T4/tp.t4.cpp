#include <iostream>
#include <memory>
#include <vector>

#include "rectangle.h"
#include "square.h"
#include "compositeShape.h"

void print(const Shape& s)
{
    Point c = s.getCenter();

    std::cout << "[" << s.getName()
        << ", (" << c.x << ", " << c.y << "), "
        << s.getArea() << "]\n";
}

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(
        Point{ 0,0 }, Point{ 4,3 }));

    shapes.push_back(std::make_unique<Rectangle>(
        Point{ -2,-1 }, Point{ 1,2 }));

    shapes.push_back(std::make_unique<Square>(
        Point{ 2,2 }, 3));

    shapes.push_back(std::make_unique<Square>(
        Point{ -3,1 }, 4));

    auto comp = std::make_unique<CompositeShape>();
    comp->addShape(std::make_unique<Rectangle>(
        Point{ 1,1 }, Point{ 3,4 }));

    comp->addShape(std::make_unique<Square>(
        Point{ 5,2 }, 2));

    shapes.push_back(std::move(comp));

    for (const auto& s : shapes)
    {
        print(*s);
    }

    std::cout << "\nScaled:\n";

    for (auto& s : shapes)
    {
        s->scale(2.0);
        print(*s);
    }

    return 0;
}
