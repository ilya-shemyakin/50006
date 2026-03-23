#include "rectangle.h"
#include <iostream>
#include <stdexcept>

Rectangle::Rectangle(const Point &BottomLeft_, const Point &TopRight_)
  : BottomLeft(BottomLeft_), TopRight(TopRight_)
{
  if (BottomLeft.x >= TopRight.x || BottomLeft.y >= TopRight.y)
  {
    throw std::invalid_argument(
      "ERROR: The coordinates of the rectangle were entered incorrectly!!!");
  }
}

double Rectangle::getArea() const
{
  return (TopRight.x - BottomLeft.x) * (TopRight.y - BottomLeft.y);
}

Point Rectangle::getCenter() const
{
  double centerX = (TopRight.x + BottomLeft.x) / 2.0;
  double centerY = (TopRight.y + BottomLeft.y) / 2.0;
  return Point(centerX, centerY);
}

void Rectangle::move(double dx, double dy)
{
  BottomLeft.x += dx;
  BottomLeft.y += dy;
  TopRight.x += dx;
  TopRight.y += dy;
}

void Rectangle::scale(double kef)
{
  if (kef <= 0)
  {
    throw std::invalid_argument("Scale kef must be positive!!!");
  }
  Point center = getCenter();

  BottomLeft.x = center.x + (BottomLeft.x - center.x) * kef;
  BottomLeft.y = center.y + (BottomLeft.y - center.y) * kef;
  TopRight.x = center.x + (TopRight.x - center.x) * kef;
  TopRight.y = center.y + (TopRight.y - center.y) * kef;
}

std::string Rectangle::getName() const
{
  return "RECTANGLE";
}
