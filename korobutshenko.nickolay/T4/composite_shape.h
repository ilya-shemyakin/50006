#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include <vector>
#include <memory>
#include "shape.h"

class CompositeShape : public Shape
{
  public:
    void addShape(std::unique_ptr<Shape>);
    size_t getSize() const;
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
    double getArea() const override;
    Point getCenter() const override;
    void move(double, double) override;
    void scale(double) override;
    std::string getName() const override;

    void print() const override;
  private:
    std::vector<std::unique_ptr<Shape>> shapes_;
    void getBoundingBox(double& minX, double& minY,
                        double& maxX, double& maxY) const override;
};

#endif
