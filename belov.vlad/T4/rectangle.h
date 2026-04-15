#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape {
public:
    Rectangle(const Point& bl, const Point& tr);
    ~Rectangle();

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;

private:
    Point bottomLeft;
    Point topRight;
};

#endif
