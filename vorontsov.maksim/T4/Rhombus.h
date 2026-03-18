#ifndef RHOMBUS_H
#define RHOMBUS_H
#include "Point.h"
#include"Shape.h"


class Rhombus : public Shape {
private:
    Point center;
    float diagonalVertical;
    float diagonalHorizontal;

public:
    Rhombus(Point centerPoint, float diagV, float diagH);

    float getArea()const override;
    Point getCenter()const override;
    void move(float dx, float dy)override;
    void scale(float coefficient)override;
    const char* getName()const override;

    float getDiagonalVertical()const {return diagonalVertical;}
    float getDiagonalHorizontal()const {return diagonalHorizontal;}
};
#endif
