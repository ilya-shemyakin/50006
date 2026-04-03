#include "ring.h"
#include <stdexcept>
#include <cmath>

Ring::Ring(const Point& center_, double outerRadius_, double innerRadius_)
    : center(center_), outerRadius(outerRadius_), innerRadius(innerRadius_)
{
    if (outerRadius_ <= 0 || innerRadius_ <= 0)
        throw std::invalid_argument("Ring radii must be positive");
    if (innerRadius_ >= outerRadius_)
        throw std::invalid_argument("Inner radius must be less than outer radius");
}

double Ring::getArea() const
{
    const double pi = 3.141592653589793;
    return pi * (outerRadius * outerRadius - innerRadius * innerRadius);
}

Point Ring::getCenter() const
{
    return center;
}

void Ring::move(double dx, double dy)
{
    center.x += dx;
    center.y += dy;
}

void Ring::scale(double factor)
{
    if (factor <= 0)
        throw std::invalid_argument("Scale factor must be positive");
    outerRadius *= factor;
    innerRadius *= factor;
}

std::string Ring::getName() const
{
    return "RING";
}
