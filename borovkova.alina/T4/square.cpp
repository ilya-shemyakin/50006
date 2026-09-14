#include "square.h"

#include <stdexcept>

Square::Square(
    const Point& bottomLeft,
    double side
) :
    bottomLeft_(bottomLeft),
    side_(side)
{
    if (side_ <= 0.0)
    {
        throw std::invalid_argument("Invalid side");
    }
}

double Square::getArea() const
{
    return side_ * side_;
}

Point Square::getCenter() const
{
    return {
        bottomLeft_.x + side_ / 2.0,
        bottomLeft_.y + side_ / 2.0
    };
}

void Square::move(double dx, double dy)
{
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
}

void Square::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Invalid scale factor");
    }

    Point center = getCenter();

    side_ *= factor;

    bottomLeft_.x = center.x - side_ / 2.0;
    bottomLeft_.y = center.y - side_ / 2.0;
}

std::string Square::getName() const
{
    return "SQUARE";
}

Point Square::getBottomLeft() const
{
    return bottomLeft_;
}

double Square::getSide() const
{
    return side_;
}   