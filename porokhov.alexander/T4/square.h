#ifndef SQUARE_H
#define SQUARE_H

#include "Shape.h"
#include "Point.h"

class Square : public Shape
{
private:
  Point BottomLeft;
  double side;

public:
  Square(const Point &BottomLeft_, double side_);

  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double kef) override;
  std::string getName() const override;
};

#endif
