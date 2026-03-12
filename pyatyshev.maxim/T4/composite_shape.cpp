#include "composite_shape.h"

CompositeShape::CompositeShape()
{
}

void CompositeShape::addShape(std::shared_ptr<Shape> shape)
{
    shapes_.push_back(shape);
}

double CompositeShape::getArea() const
{
    double totalArea = 0.0;
    for (const auto &shape : shapes_)
    {
        totalArea += shape->getArea();
    }
    return totalArea;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty())
    {
        return Point(0, 0);
    }

    double totalArea = 0.0;
    double centerX = 0.0;
    double centerY = 0.0;

    for (const auto &shape : shapes_)
    {
        double area = shape->getArea();
        Point center = shape->getCenter();

        totalArea += area;
        centerX += center.x * area;
        centerY += center.y * area;
    }

    return Point(centerX / totalArea, centerY / totalArea);
}

void CompositeShape::move(double dx, double dy)
{
    for (auto &shape : shapes_)
    {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    for (auto &shape : shapes_)
    {
        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE_SHAPE";
}
