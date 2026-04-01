#include "isosceles_trapezoid.h"

IsoscelesTrapezoid::IsoscelesTrapezoid(const Point& leftBottom, double lengthBottom,
                                       double lengthTop, double height) :
  leftBottom_(leftBottom),
  lengthBottom_(lengthBottom),
  lengthTop_(lengthTop),
  height_(height)
{
  if (lengthBottom <= 0 || lengthTop <= 0 || height <= 0)
  {
    throw std::invalid_argument("incorrect value");
  }
};

double IsoscelesTrapezoid::getArea() const
{
  return (lengthBottom_ + lengthTop_) / 2.0 * height_;
}

Point IsoscelesTrapezoid::getLeftTop() const
{
  double dX = (lengthBottom_ - lengthTop_) / 2.0;
  Point result(leftBottom_.getX() + dX, leftBottom_.getY() + height_);
  return result;
}

Point IsoscelesTrapezoid::getRightBottom() const
{
  Point result(leftBottom_.getX() + lengthBottom_, leftBottom_.getY());
  return result;
}

Point IsoscelesTrapezoid::getRightTop() const
{
  Point leftTop = getLeftTop();
  Point result(leftTop.getX() + lengthTop_, leftTop.getY());
  return result;
}

Point IsoscelesTrapezoid::getCenter() const
{
  Point rightBottom = getRightBottom();
  Point leftTop = getLeftTop();
  Point rightTop = getRightTop();

  Point leftMid((leftBottom_.getX() + leftTop.getX()) / 2.0,
                (leftBottom_.getY() + leftTop.getY()) / 2.0);

  Point rightMid((rightBottom.getX() + rightTop.getX()) / 2.0,
                 (rightBottom.getY() + rightTop.getY()) / 2.0);

  Point center((leftMid.getX() + rightMid.getX()) / 2.0,
               (leftMid.getY() + rightMid.getY()) / 2.0);

  return center;
}

void IsoscelesTrapezoid::move(double x, double y)
{
  leftBottom_.setX(leftBottom_.getX() + x);
  leftBottom_.setY(leftBottom_.getY() + y);
}

void IsoscelesTrapezoid::scale(double scale)
{
  if (scale <= 0)
  {
    throw std::invalid_argument("incorrect scale value");
  }

  Point center = getCenter();

  double leftBottomX = center.getX() + (leftBottom_.getX() - center.getX()) * scale;
  double leftBottomY = center.getY() + (leftBottom_.getY() - center.getY()) * scale;

  leftBottom_.setX(leftBottomX);
  leftBottom_.setY(leftBottomY);

  height_ *= scale;
  lengthBottom_ *= scale;
  lengthTop_ *= scale;
}

std::string IsoscelesTrapezoid::getName() const
{
  return "ISOSCELES_TRAPEZOID";
}

void IsoscelesTrapezoid::getBoundingBox(double& minX, double& minY,
                                        double& maxX, double& maxY) const
{
  Point leftTop = getLeftTop();
  Point rightBottom = getRightBottom();
  Point rightTop = getRightTop();
  minX = leftBottom_.getX() < leftTop.getX() ? leftBottom_.getX() : leftTop.getX();
  maxX = rightBottom.getX() > rightTop.getX() ? rightBottom.getX() : rightTop.getX();
  minY = leftBottom_.getY();
  maxY = leftTop.getY();
}

void IsoscelesTrapezoid::print() const
{
  Point center = getCenter();
  std::cout << "[" << getName() << ", ("
            << std::fixed << std::setprecision(2) << center.getX()
            << ", " << std::setprecision(2) << center.getY() << "), "
            << std::setprecision(2) << getArea() << "]";
}
