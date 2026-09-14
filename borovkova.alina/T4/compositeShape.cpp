#include "compositeShape.h"

#include <stdexcept>

#include "rectangle.h"
#include "square.h"

void CompositeShape::addShape(
    std::unique_ptr<Shape> shape
)
{
    if (!shape)
    {
        throw std::invalid_argument("Null shape");
    }

    if (dynamic_cast<CompositeShape*>(shape.get()))
    {
        throw std::invalid_argument(
            "Composite cannot contain another composite"
        );
    }

    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
    double area = 0.0;

    for (const auto& shape : shapes_)
    {
        area += shape->getArea();
    }

    return area;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty())
    {
        throw std::logic_error("Composite shape is empty");
    }

    bool first = true;

    double minX = 0.0;
    double maxX = 0.0;
    double minY = 0.0;
    double maxY = 0.0;

    for (const auto& shape : shapes_)
    {
        double left;
        double right;
        double bottom;
        double top;

        if (const Rectangle* rectangle =
            dynamic_cast<const Rectangle*>(shape.get()))
        {
            Point bottomLeft =
                rectangle->getBottomLeft();

            Point topRight =
                rectangle->getTopRight();

            left = bottomLeft.x;
            right = topRight.x;

            bottom = bottomLeft.y;
            top = topRight.y;
        }
        else if (const Square* square =
            dynamic_cast<const Square*>(shape.get()))
        {
            Point bottomLeft =
                square->getBottomLeft();

            double side =
                square->getSide();

            left = bottomLeft.x;
            right = bottomLeft.x + side;

            bottom = bottomLeft.y;
            top = bottomLeft.y + side;
        }
        else
        {
            continue;
        }

        if (first)
        {
            minX = left;
            maxX = right;

            minY = bottom;
            maxY = top;

            first = false;
        }
        else
        {
            if (left < minX)
                minX = left;

            if (right > maxX)
                maxX = right;

            if (bottom < minY)
                minY = bottom;

            if (top > maxY)
                maxY = top;
        }
    }

    return {
        (minX + maxX) / 2.0,
        (minY + maxY) / 2.0
    };
}

void CompositeShape::move(
    double dx,
    double dy
)
{
    for (auto& shape : shapes_)
    {
        shape->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument(
            "Invalid scale factor"
        );
    }

    Point center = getCenter();

    for (auto& shape : shapes_)
    {
        Point shapeCenter =
            shape->getCenter();

        double newCenterX =
            center.x +
            (shapeCenter.x - center.x) * factor;

        double newCenterY =
            center.y +
            (shapeCenter.y - center.y) * factor;

        shape->move(
            newCenterX - shapeCenter.x,
            newCenterY - shapeCenter.y
        );

        shape->scale(factor);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>&
CompositeShape::getShapes() const
{
    return shapes_;
}
