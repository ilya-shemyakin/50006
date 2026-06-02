#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H

#include "shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape {
public:
    CompositeShape();
    ~CompositeShape();

    void addShape(std::unique_ptr<Shape> shape);
    double getArea() const override;
    Point getCenter() const override;
    void move(double dx, double dy) override;
    void scale(double factor) override;
    const char* getName() const override;

    const Shape& getShape(size_t index) const;
    size_t getSize() const;
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;

private:
    std::vector<std::unique_ptr<Shape>> shapes;
};

#endif
