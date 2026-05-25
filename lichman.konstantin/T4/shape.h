#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "point.h"

class Shape
{
public:
    virtual ~Shape() = 0;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double newX, double newY) = 0;
    virtual void scale(double k) = 0;
    virtual std::string getName() const = 0;
};

#endif

