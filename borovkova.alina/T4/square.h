#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape
{
public:
    Square(const Point& bottomLeft, double side);

    double getArea() const override;
    Point getCenter() const override;

    void move(double dx, double dy) override;
    void scale(double factor) override;

    std::string getName() const override;

    Point getBottomLeft() const;
    double getSide() const;

private:
    Point bottomLeft_;
    double side_;
};

#endif
