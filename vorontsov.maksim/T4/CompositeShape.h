#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include "Point.h"
#include "Shape.h"
#include <vector>
#include <memory>

class CompositeShape : public Shape
{
private:
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    CompositeShape();
    void addShape(std::unique_ptr<Shape> shape);

    float getArea()const override;
    Point getCenter()const override;
    void move(float dx, float dy)override;
    void scale(float coefficient)override;
    const char* getName()const override;

    size_t getShapesCount()const {return shapes.size();}

    const Shape& getShape(size_t index) const;

};
#endif
