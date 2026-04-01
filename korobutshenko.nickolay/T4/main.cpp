#include <vector>
#include "rectangle.h"
#include "isosceles_trapezoid.h"
#include "composite_shape.h"

int main()
{
  try
  {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Rectangle>(
      Point(1.0, 2.0), Point(5.0, 4.0)));

    shapes.push_back(std::make_unique<Rectangle>(
      Point(1.0, 1.0), Point(3.0, 3.0)));

    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(
      Point(2.0, 1.0), 6.0, 4.0, 3.0));

    shapes.push_back(std::make_unique<IsoscelesTrapezoid>(
      Point(5.0, 2.0), 2.0, 4.0, 2.5));

    std::unique_ptr<CompositeShape> composite = std::make_unique<CompositeShape>();

    std::unique_ptr<Rectangle> rect1 = std::make_unique<Rectangle>(Point(0.0, 0.0),
                                                                   Point(2.0, 3.0));
    composite->addShape(std::move(rect1));

    std::unique_ptr<IsoscelesTrapezoid> trap1 = std::make_unique<IsoscelesTrapezoid>(
    Point(3.0, 1.0), 4.0, 2.0, 2.0);
    composite->addShape(std::move(trap1));

    shapes.push_back(std::move(composite));
    size_t sizeOfShapes = shapes.size();

    for (size_t i = 0; i < sizeOfShapes; ++i)
    {
      shapes[i]->print();
      std::cout << "\n";
    }

    std::cout << "\nafter Scale(2)\n" << std::endl;
    for (size_t i = 0; i < sizeOfShapes; ++i)
    {
      shapes[i]->scale(2.0);
    }

    for (size_t i = 0; i < sizeOfShapes; ++i)
    {
      shapes[i]->print();
      std::cout << "\n";
    }
  }
  catch (const std::exception& e)
  {
    std::cout << e.what();
  }
  return 0;
}
