#include "rectangle.h"
#include "isosceles_trapezoid.h"
#include "composite_shape.h"
#include <iostream>
#include <memory>
#include <iomanip>

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    Rectangle rect(Point(0, 0), Point(4, 3));
    std::cout << "Rectangle: " << rect.getName() << std::endl;
    std::cout << "Area: " << rect.getArea() << std::endl;
    std::cout << "Center: (" << rect.getCenter().x << ", "
              << rect.getCenter().y << ")" << std::endl;

    rect.move(1, 1);
    std::cout << "After move: Center: (" << rect.getCenter().x << ", "
              << rect.getCenter().y << ")" << std::endl;

    rect.scale(2);
    std::cout << "After scale: Area: " << rect.getArea() << std::endl;

    std::cout << std::endl;

    IsoscelesTrapezoid trap(Point(0, 0), Point(6, 0),
                            Point(1, 4), Point(5, 4));
    std::cout << "Isosceles Trapezoid: " << trap.getName() << std::endl;
    std::cout << "Area: " << trap.getArea() << std::endl;
    std::cout << "Center: (" << trap.getCenter().x << ", "
              << trap.getCenter().y << ")" << std::endl;

    trap.move(2, 2);
    std::cout << "After move: Center: (" << trap.getCenter().x << ", "
              << trap.getCenter().y << ")" << std::endl;

    trap.scale(1.5);
    std::cout << "After scale: Area: " << trap.getArea() << std::endl;

    std::cout << std::endl;

    CompositeShape composite;
    composite.addShape(std::make_shared<Rectangle>(Point(0, 0), Point(2, 2)));
    composite.addShape(std::make_shared<IsoscelesTrapezoid>(
        Point(3, 0), Point(7, 0), Point(4, 3), Point(6, 3)));

    std::cout << "Composite Shape: " << composite.getName() << std::endl;
    std::cout << "Total Area: " << composite.getArea() << std::endl;
    std::cout << "Center: (" << composite.getCenter().x << ", "
              << composite.getCenter().y << ")" << std::endl;

    return 0;
}
