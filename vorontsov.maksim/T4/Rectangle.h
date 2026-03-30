#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:

    Rectangle( const Point& bL, const Point& tR);

    float getArea()const override;
    Point getCenter()const override;
    void move(float dx, float dy)override;
    void scale(float coefficient)override;
    const char* getName()const override;

private:
    Point bl;
    Point tr;
};
#endif
