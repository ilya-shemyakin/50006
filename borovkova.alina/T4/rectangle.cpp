#include "rectangle.h"

#include <stdexcept>

Rectangle::Rectangle(
    const Point& bottomLeft,
    const Point& topRight
) :
    bottomLeft_(bottomLeft),
    topRight_(topRight)
{
    if (topRight_.x <= bottomLeft_.x ||
        topRight_.y <= bottomLeft_.y)
    {
        throw std::invalid_argument("Invalid rectangle");
    }
}

double Rectangle::getArea() const
{
    double width = topRight_.x - bottomLeft_.x;
    double height = topRight_.y - bottomLeft_.y;

    return width * height;
}

Point Rectangle::getCenter() const
{
    return {
        (bottomLeft_.x + topRight_.x) / 2.0,
        (bottomLeft_.y + topRight_.y) / 2.0
    };
}

void Rectangle::move(double dx, double dy)
{
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;

    topRight_.x += dx;
    topRight_.y += dy;
}

void Rectangle::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Invalid scale factor");
    }

    Point center = getCenter();

    double halfWidth =
        (topRight_.x - bottomLeft_.x) / 2.0 * factor;

    double halfHeight =
        (topRight_.y - bottomLeft_.y) / 2.0 * factor;

    bottomLeft_ = {
        center.x - halfWidth,
        center.y - halfHeight
    };

    topRight_ = {
        center.x + halfWidth,
        center.y + halfHeight
    };
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}

Point Rectangle::getBottomLeft() const
{
    return bottomLeft_;
}

Point Rectangle::getTopRight() const
{
    return topRight_;
}
