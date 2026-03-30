#include "square.h"
#include <iostream>
#include <stdexcept>

Square::Square(const Point &BottomLeft_, double side_)
  : BottomLeft(BottomLeft_), side(side_)
{
  if (side <= 0)
  {
    throw std::invalid_argument("Square side must be positive!!!");
  }
}

double Square::getArea() const
{
  return side * side;
}

Point Square::getCenter() const
{
  double centerX = BottomLeft.x + side / 2.0;
  double centerY = BottomLeft.y + side / 2.0;
  return Point(centerX, centerY);
}

void Square::move(double dx, double dy)
{
  BottomLeft.x += dx;
  BottomLeft.y += dy;
}

void Square::scale(double kef)
{
  if (kef <= 0)
  {
    throw std::invalid_argument("Square kef must be positive!!!");
  }
  Point center = getCenter();
  side *= kef;
  BottomLeft.x = center.x - side / 2.0;
  BottomLeft.y = center.y - side / 2.0;
}

std::string Square::getName() const
{
  return "SQUARE";
}
