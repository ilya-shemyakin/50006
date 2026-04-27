#include "rectangle.h"
#include "isosceles_trapezoid.h"
#include "composite_shape.h"
#include <iostream>
#include <memory>
#include <iomanip>

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    auto rect = std::make_unique<Rectangle>(Point(0, 0), Point(4, 3));
    auto trap = std::make_unique<IsoscelesTrapezoid>(Point(5, 0), 6.0, 4.0, 4.0);

    CompositeShape composite;
    composite.addShape(std::make_unique<Rectangle>(Point(10, 10), Point(12, 14)));
    composite.addShape(std::make_unique<IsoscelesTrapezoid>(Point(0, 10), 5.0, 3.0, 2.0));

    std::cout << "[" << rect->getName() << ",(" << rect->getCenter().x << ", "
              << rect->getCenter().y << "), " << rect->getArea() << "]" << std::endl;

    std::cout << "[" << trap->getName() << ",(" << trap->getCenter().x << ", "
              << trap->getCenter().y << "), " << trap->getArea() << "]" << std::endl;

    std::cout << "[" << composite.getName() << ",(" << composite.getCenter().x << ", "
              << composite.getCenter().y << "), " << composite.getArea()
              << ": " << composite.getDetails() << "]" << std::endl;

    rect->scale(2.0);
    trap->scale(2.0);
    composite.scale(2.0);

    std::cout << "[" << rect->getName() << ",(" << rect->getCenter().x << ", "
              << rect->getCenter().y << "), " << rect->getArea() << "]" << std::endl;

    std::cout << "[" << trap->getName() << ",(" << trap->getCenter().x << ", "
              << trap->getCenter().y << "), " << trap->getArea() << "]" << std::endl;

    std::cout << "[" << composite.getName() << ",(" << composite.getCenter().x << ", "
              << composite.getCenter().y << "), " << composite.getArea()
              << ": " << composite.getDetails() << "]" << std::endl;

    return 0;
}
