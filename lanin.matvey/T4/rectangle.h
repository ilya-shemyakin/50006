#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
private:
  Point BottomLeft;
  Point TopRight;

public:
  Rectangle(const Point& BottomLeft_, const Point& TopRight_);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double kef) override;
  std::string getName() const override;
};

#endif
