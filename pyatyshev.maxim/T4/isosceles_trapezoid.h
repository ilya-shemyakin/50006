#ifndef ISOSCELES_TRAPEZOID_H
#define ISOSCELES_TRAPEZOID_H

#include "shape.h"

class IsoscelesTrapezoid : public Shape
{
private:
    Point bottomLeft_;
    Point bottomRight_;
    Point topLeft_;
    Point topRight_;

public:
    IsoscelesTrapezoid(Point bottomLeft, Point bottomRight,
                       Point topLeft, Point topRight);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif
