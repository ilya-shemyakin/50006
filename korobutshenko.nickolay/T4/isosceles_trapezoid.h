#ifndef ISOSCELES_TRAPEZOID_H
#define ISOSCELES_TRAPEZOID_H

#include "shape.h"

class IsoscelesTrapezoid : public Shape
{
  public:

    IsoscelesTrapezoid(const Point&, double, double, double);

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
    double lengthBottom_;
    double lengthTop_;
    double height_;
    
    Point getLeftTop() const;
    Point getRightBottom() const;
    Point getRightTop() const;
};

#endif
