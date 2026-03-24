#include "rectangle.h"

Rectangle::Rectangle(const Point& leftBottom, const Point& rightTop_) :
  leftBottom_(leftBottom),
  rightTop_(rightTop_)
{
  if (leftBottom.getX() >= rightTop_.getX() || leftBottom.getY() >= rightTop_.getY())
  {
    throw std::invalid_argument("incorrect coordinates");
  }
}

double Rectangle::getArea() const 
{
  double width = rightTop_.getX() - leftBottom_.getX();
  double height = rightTop_.getY() - leftBottom_.getY();
  return width * height;
}

Point Rectangle::getCenter() const
{
  double centerX = (rightTop_.getX() + leftBottom_.getX()) / 2.0;
  double centerY = (rightTop_.getY() + leftBottom_.getY()) / 2.0;
  return Point(centerX, centerY);
}

void Rectangle::move(double x, double y)
{
  leftBottom_.setX(leftBottom_.getX() + x);
  leftBottom_.setY(leftBottom_.getY() + y);
  rightTop_.setX(rightTop_.getX() + x);
  rightTop_.setY(rightTop_.getY() + y);
}

void Rectangle::scale(double scale)
{
  if (scale <= 0.0)
  {
    throw std::invalid_argument("incorrect scale value");
  }

  Point center = getCenter();

  double leftBottomX = center.getX() + (leftBottom_.getX() - center.getX()) * scale;
  double leftBottomY = center.getY() + (leftBottom_.getY() - center.getY()) * scale;
  double rightTopX = center.getX() + (rightTop_.getX() - center.getX()) * scale;
  double rightTopY = center.getY() + (rightTop_.getY() - center.getY()) * scale;

  leftBottom_.setX(leftBottomX);
  leftBottom_.setY(leftBottomY);
  rightTop_.setX(rightTopX);
  rightTop_.setY(rightTopY);
}

std::string Rectangle::getName() const
{
  return "RECTANGLE";
}

void Rectangle::getBoundingBox(double& minX, double& minY,
                               double& maxX, double& maxY) const
{
  minX = leftBottom_.getX() < rightTop_.getX() ? leftBottom_.getX() : rightTop_.getX();
  minY = leftBottom_.getY() < rightTop_.getY() ? leftBottom_.getY() : rightTop_.getY();
  maxX = leftBottom_.getX() > rightTop_.getX() ? leftBottom_.getX() : rightTop_.getX();
  maxY = leftBottom_.getY() > rightTop_.getY() ? leftBottom_.getY() : rightTop_.getY();
}

void Rectangle::print() const
{
  Point center = getCenter();
  std::cout << "[" << getName() << ", ("  
            << std::fixed << std::setprecision(2) << center.getX()  
            << ", " << std::setprecision(2) << center.getY() << "), "  
            << std::setprecision(2) << getArea() << "]";
}
