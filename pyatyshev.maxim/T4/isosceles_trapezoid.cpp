#include "isosceles_trapezoid.h"
#include <cmath>
#include <algorithm>

IsoscelesTrapezoid::IsoscelesTrapezoid(Point bottomLeft, double bottomBase,
                                       double topBase, double height)
    : bottomLeft_(bottomLeft), bottomBase_(bottomBase),
      topBase_(topBase), height_(height)
{
}

double IsoscelesTrapezoid::getArea() const
{
    return (bottomBase_ + topBase_) * height_ / 2.0;
}

Point IsoscelesTrapezoid::getCenter() const
{
    double centerX = bottomLeft_.x + bottomBase_ / 2.0;
    double centerY = bottomLeft_.y + height_ / 2.0;
    return Point(centerX, centerY);
}

void IsoscelesTrapezoid::move(double dx, double dy)
{
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
}

void IsoscelesTrapezoid::scale(double factor)
{
    Point center = getCenter();
    bottomLeft_.x = center.x + (bottomLeft_.x - center.x) * factor;
    bottomLeft_.y = center.y + (bottomLeft_.y - center.y) * factor;
    bottomBase_ *= factor;
    topBase_ *= factor;
    height_ *= factor;
}

std::string IsoscelesTrapezoid::getName() const
{
    return "ISOSCELES_TRAPEZOID";
}

double IsoscelesTrapezoid::getLeft() const
{
    double offset = (bottomBase_ - topBase_) / 2.0;
    return bottomLeft_.x + std::min(0.0, offset);
}

double IsoscelesTrapezoid::getRight() const
{
    double offset = (bottomBase_ - topBase_) / 2.0;
    return bottomLeft_.x + bottomBase_ + std::max(0.0, offset);
}

double IsoscelesTrapezoid::getBottom() const
{
    return bottomLeft_.y;
}

double IsoscelesTrapezoid::getTop() const
{
    return bottomLeft_.y + height_;
}

