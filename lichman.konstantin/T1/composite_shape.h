#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <memory>
#include <vector>

class CompositeShape : public Shape {
public:
  void add(std::shared_ptr<Shape> shape);
  double getArea() const override;
  Point getCenter() const override;
  void move(double dx, double dy) override;
  void scale(double factor) override;
  std::string getName() const override;

private:
  std::vector<std::shared_ptr<Shape>> shapes_;
};

#endif