#pragma once
#include "Point.h"
#include "Shape.h"

class Rectangle : public Shape
{
public:

    Rectangle(Point bL, Point tR);

    float getArea() const override;
    Point getCenter() const override;
    void move(float dx, float dy) override;
    void scale(float coefficient) override;
    const char* getName() const override;

    Point getBottomLeft() const { return bl; }
    Point getTopRight() const { return tr; }

private:
    Point bl;
    Point tr;
};
