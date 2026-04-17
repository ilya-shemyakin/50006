#ifndef COMPOSITESHAPE.H
#defibe COMPOSITESHAPE.H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
private:
    std::vector<std::shared_ptr<Shape>> shapes_;

public:
    CompositeShape() = default;

    void addShape(const std::shared_ptr<Shape>& shape);

    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    std::string getName() const override;
};

#endif

