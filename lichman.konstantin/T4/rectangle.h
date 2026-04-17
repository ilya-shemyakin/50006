#ifndef RECTANGLE_H
#indef RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape
{
private:
    Point leftBottom_;
    Point rightTop_;
public:
    Rectangle(const Point& leftBottom, const Point& rightTop);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double k) override;
    std::string getName() const override;
};

#endif

