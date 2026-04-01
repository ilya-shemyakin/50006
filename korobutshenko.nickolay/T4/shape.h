#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "point.h"

class Shape
{
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double, double) = 0;
    virtual void scale(double) = 0;
    virtual std::string getName() const = 0;

    virtual void getBoundingBox(double& minX, double& minY,
                                double& maxX, double& maxY) const = 0;

    virtual void print() const = 0;
};

#endif
