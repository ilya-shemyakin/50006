#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

class Rectangle : public Shape 
{
  public:

    Rectangle(const Point&, const Point&);

    double getArea() const override;
    Point getCenter() const override;
    void move(double, double) override;
    void scale(double) override;
    std::string getName() const override;

    void getBoundingBox(double& minX, double& minY,  
                        double& maxX, double& maxY) const override;

    void print() const override;
  private:
    Point leftBottom_;
    Point rightTop_;
};

#endif
