#include "composite_shape.h"
#include <algorithm>
#include <limits>
#include <stdexcept>

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
  if (!shape)
  {
    throw std::invalid_argument(
      "CompositeShape cannot add null shape!!!");
  }
  shapes.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
  double totalArea = 0.0;
  for (const std::unique_ptr<Shape> &shape : shapes)
  {
    totalArea += shape->getArea();
  }
  return totalArea;
}

Point CompositeShape::getCenter() const
{
  if (shapes.empty())
  {
    return Point(0, 0);
  }

  double minX = std::numeric_limits<double>::max();
  double minY = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double maxY = std::numeric_limits<double>::lowest();
  for (const std::unique_ptr<Shape> &shape : shapes)
  {
    Point center = shape->getCenter();
    minX = std::min(minX, center.x);
    minY = std::min(minY, center.y);
    maxX = std::max(maxX, center.x);
    maxY = std::max(maxY, center.y);
  }
  return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CompositeShape::move(double dx, double dy)
{
  for (std::unique_ptr<Shape> &shape : shapes)
  {
    shape->move(dx, dy);
  }
}

void CompositeShape::scale(double kef)
{
  if (kef <= 0)
  {
    throw std::invalid_argument("Scale kef must be positive!!!");
  }
  if (shapes.empty())
  {
    return;
  }

  Point CompositeCenter = getCenter();

  for (std::unique_ptr<Shape> &shape : shapes)
  {
    Point shapeCenter = shape->getCenter();

    double dx = shapeCenter.x - CompositeCenter.x;
    double dy = shapeCenter.y - CompositeCenter.y;

    double newDx = dx * kef;
    double newDy = dy * kef;

    shape->move(newDx - dx, newDy - dy);
    shape->scale(kef);
  }
}

std::string CompositeShape::getName() const
{
  return "COMPOSITE";
}

size_t CompositeShape::getSize() const
{
  return shapes.size();
}

const std::vector<std::unique_ptr<Shape>>&
CompositeShape::getShapes() const
{
  return shapes;
}
