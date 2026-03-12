#ifndef ISOSCELES_TRAPEZOID_H
#define ISOSCELES_TRAPEZOID_H

#include "shape.h"

class IsoscelesTrapezoid : public Shape
{
private:
    Point bottomLeft_;
    double bottomBase_;
    double topBase_;
    double height_;

public:
    IsoscelesTrapezoid(Point bottomLeft, double bottomBase,
                       double topBase, double height);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
    double getLeft() const;
    double getRight() const;
    double getBottom() const;
    double getTop() const;
};

#endif
