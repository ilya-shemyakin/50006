#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class Ellipse : public Shape {

public:
    Ellipse(const Point& c, double rx, double ry);
    ~Ellipse();

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;

private:
    Point center;
    double radiusX;
    double radiusY;
};

#endif
