#include "composite_shape.h"

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
  if (shape)
  {
    shapes_.push_back(std::move(shape));
  }
}

size_t CompositeShape::getSize() const
{
  return shapes_.size();
}

const std::vector<std::unique_ptr<Shape>>& CompositeShape::getShapes() const
{
  return shapes_;
}

double CompositeShape::getArea() const
{
  double totalArea = 0.0;
  for (size_t i = 0; i < shapes_.size(); ++i)
  {
    totalArea += shapes_[i]->getArea();
  }
  return totalArea;
}

void CompositeShape::getBoundingBox(double& minX, double& minY,
                                    double& maxX, double& maxY) const
{
  bool isFirst = 1;
  double shapeMinX = 0.0;
  double shapeMaxX = 0.0;
  double shapeMinY = 0.0;
  double shapeMaxY = 0.0;
  for (size_t i = 0; i < shapes_.size(); ++i)
  {
    shapes_[i]->getBoundingBox(shapeMinX, shapeMinY, shapeMaxX, shapeMaxY);
    if (isFirst)
    {
      minX = shapeMinX;
      maxX = shapeMaxX;
      minY = shapeMinY;
      maxY = shapeMaxY;
      isFirst = 0;
    }
    else
    {
      minX = (minX < shapeMinX) ? minX : shapeMinX;
      minY = (minY < shapeMinY) ? minY : shapeMinY;
      maxX = (maxX > shapeMaxX) ? maxX : shapeMaxX;
      maxY = (maxY > shapeMaxY) ? maxY : shapeMaxY;
    }
  }
}

Point CompositeShape::getCenter() const
{
  double minX = 0.0;
  double minY = 0.0;
  double maxX = 0.0;
  double maxY = 0.0;
  getBoundingBox(minX, minY, maxX, maxY);
  double centerX = (minX + maxX) / 2.0;
  double centerY = (minY + maxY) / 2.0;
  return Point(centerX, centerY);
}

void CompositeShape::move(double x, double y)
{
  for (size_t i = 0; i < shapes_.size(); ++i)
  {
    shapes_[i]->move(x, y);
  }
}

void CompositeShape::scale(double scale)
{
  if (scale <= 0)
  {
    return;
  }
  Point compositeCenter = getCenter();

  for (size_t i = 0; i < shapes_.size(); ++i)
  {
    Point shapeCenter = shapes_[i]->getCenter();

    double dX = shapeCenter.getX() - compositeCenter.getX();
    double dY = shapeCenter.getY() - compositeCenter.getY();

    double newDX = dX * scale;
    double newDY = dY * scale;

    double newCenterX = compositeCenter.getX() + newDX;
    double newCenterY = compositeCenter.getY() + newDY;

    shapes_[i]->move(newCenterX - shapeCenter.getX(),
                     newCenterY - shapeCenter.getY());

    shapes_[i]->scale(scale);
  }
}

std::string CompositeShape::getName() const
{
  return "COMPOSITE_SHAPE";
}

void CompositeShape::print() const
{
  Point center = getCenter();
  size_t size = getSize();
  std::cout << "[" << getName() << ", ("
            << std::fixed << std::setprecision(2) << center.getX()
            << ", " << std::setprecision(2) << center.getY() << "), "
            << std::setprecision(2) << getArea() << ":\n";
  for (size_t i = 0; i < size; ++i)
  {
    std::cout << " ";
    shapes_[i]->print();
    if (i < size - 1)
    {
      std::cout << ",";
    }
    std::cout << "\n";
  }
  std::cout << "]";
}
