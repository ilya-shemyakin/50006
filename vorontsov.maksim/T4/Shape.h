#pragma once
#include "Point.h"

class Shape
{
public:
    virtual ~Shape()= default;
    virtual float getArea()const = 0;
    virtual Point getCenter()const = 0;
    virtual void move(float x_, float y_)= 0;
    virtual void scale(float multiplier)= 0;
    virtual const char* getName()const = 0;
};
