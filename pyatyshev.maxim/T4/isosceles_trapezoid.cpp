#include "isosceles_trapezoid.h"
#include <cmath>

IsoscelesTrapezoid::IsoscelesTrapezoid(Point bottomLeft, Point bottomRight,
                                       Point topLeft, Point topRight)
    : bottomLeft_(bottomLeft), bottomRight_(bottomRight),
      topLeft_(topLeft), topRight_(topRight)
{
}

double IsoscelesTrapezoid::getArea() const
{
    double bottomBase = bottomRight_.x - bottomLeft_.x;
    double topBase = topRight_.x - topLeft_.x;
    double height = bottomLeft_.y - topLeft_.y;

    return (bottomBase + topBase) * height / 2.0;
}

Point IsoscelesTrapezoid::getCenter() const
{
    double centerX = (bottomLeft_.x + bottomRight_.x + topLeft_.x + topRight_.x) / 4.0;
    double centerY = (bottomLeft_.y + bottomRight_.y + topLeft_.y + topRight_.y) / 4.0;

    return Point(centerX, centerY);
}

void IsoscelesTrapezoid::move(double dx, double dy)
{
    bottomLeft_.x += dx;
    bottomLeft_.y += dy;
    bottomRight_.x += dx;
    bottomRight_.y += dy;
    topLeft_.x += dx;
    topLeft_.y += dy;
    topRight_.x += dx;
    topRight_.y += dy;
}

void IsoscelesTrapezoid::scale(double factor)
{
    Point center = getCenter();

    bottomLeft_.x = center.x + (bottomLeft_.x - center.x) * factor;
    bottomLeft_.y = center.y + (bottomLeft_.y - center.y) * factor;

    bottomRight_.x = center.x + (bottomRight_.x - center.x) * factor;
    bottomRight_.y = center.y + (bottomRight_.y - center.y) * factor;

    topLeft_.x = center.x + (topLeft_.x - center.x) * factor;
    topLeft_.y = center.y + (topLeft_.y - center.y) * factor;

    topRight_.x = center.x + (topRight_.x - center.x) * factor;
    topRight_.y = center.y + (topRight_.y - center.y) * factor;
}

std::string IsoscelesTrapezoid::getName() const
{
    return "ISOSCELES_TRAPEZOID";
}
