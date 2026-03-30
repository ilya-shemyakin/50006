#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include "rectangle.h"
#include "square.h"
#include "composite_shape.h"

void printShape(const Shape &shape)
{
  Point center = shape.getCenter();
  std::cout << "[" << shape.getName() << ", ("
            << std::fixed << std::setprecision(2) << center.x
            << ", " << std::setprecision(2) << center.y << "), "
            << std::setprecision(2) << shape.getArea() << "]";
}

void printComposite(const CompositeShape &composite)
{
  Point center = composite.getCenter();
  std::cout << "[" << composite.getName() << ", ("
            << std::fixed << std::setprecision(2) << center.x
            << ", " << std::setprecision(2) << center.y << "), "
            << std::setprecision(2) << composite.getArea() << ":\n";

  const std::vector<std::unique_ptr<Shape>> &shapes =
    composite.getShapes();
  for (size_t i = 0; i < shapes.size(); ++i)
  {
    std::cout << "  ";
    printShape(*shapes[i]);
    if (i < shapes.size() - 1)
    {
      std::cout << ",";
    }
    std::cout << "\n";
  }
  std::cout << "]";
}

int main()
{
  try
  {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(
      std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    shapes.push_back(
      std::make_unique<Square>(Point(1, 1), 2));
    shapes.push_back(
      std::make_unique<Rectangle>(Point(-2, -1), Point(2, 1)));

    auto composite1 = std::make_unique<CompositeShape>();
    composite1->addShape(
      std::make_unique<Rectangle>(Point(5, 5), Point(7, 8)));
    composite1->addShape(
      std::make_unique<Square>(Point(10, 10), 3));
    shapes.push_back(std::move(composite1));

    auto composite2 = std::make_unique<CompositeShape>();
    composite2->addShape(
      std::make_unique<Rectangle>(Point(-5, -5), Point(-1, -2)));
    shapes.push_back(std::move(composite2));

    std::cout << "BEFORE SCALE:\n";
    for (const auto &shape : shapes)
    {
      const CompositeShape *composite =
        dynamic_cast<const CompositeShape *>(shape.get());
      if (composite)
      {
        printComposite(*composite);
      }
      else
      {
        printShape(*shape);
      }
      std::cout << "\n";
    }

    for (auto &shape : shapes)
    {
      shape->scale(2.0);
    }

    std::cout << "==========================================\n";

    std::cout << "AFTER SCALE:\n";
    for (const auto &shape : shapes)
    {
      const CompositeShape *composite =
        dynamic_cast<const CompositeShape *>(shape.get());
      if (composite)
      {
        printComposite(*composite);
      }
      else
      {
        printShape(*shape);
      }
      std::cout << "\n";
    }
  }
  catch (const std::exception &e)
  {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
