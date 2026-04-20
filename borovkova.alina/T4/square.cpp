#include "square.h"
#include <stdexcept>

Square::Square(const Point& center, double side) :
    center_(center),
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
    return center_;
}

void Square::move(double dx, double dy)
{
    center_.x += dx;
    center_.y += dy;
}

void Square::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Invalid scale");
    }

    side_ *= factor;
}

std::string Square::getName() const
{
    return "SQUARE";
}

double Square::getSide() const
{
    return side_;
}