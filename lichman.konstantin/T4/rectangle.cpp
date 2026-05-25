#include "rectangle.h"

Rectangle::Rectangle(const Point& leftBottom, const Point& rightTop) :
    leftBottom_(leftBottom), rightTop_(rightTop)
{
}

double Rectangle::getArea() const
{
    return (rightTop_.y - leftBottom_.y) *
        (rightTop_.x - leftBottom_.x);
}

Point Rectangle::getCenter() const
{
    Point center;
    center.x = (leftBottom_.x + rightTop_.x) / 2.0;
    center.y = (leftBottom_.y + rightTop_.y) / 2.0;
    return center;
}

void Rectangle::move(double dx, double dy)
{
    leftBottom_.x += dx;
    leftBottom_.y += dy;
    rightTop_.x += dx;
    rightTop_.y += dy;
}

void Rectangle::scale(double k)
{
    Point center = getCenter();

    leftBottom_.x = (center.x - leftBottom_.x) * k + center.x;
    leftBottom_.y = (center.y - leftBottom_.y) * k + center.y;

    rightTop_.x = (center.x - rightTop_.x) * k + center.x;
    rightTop_.x = (center.x - rightTop_.x) * k + center.x;
}

std::string Rectangle::getName() const
{
    return "RECTANGLE";
}
