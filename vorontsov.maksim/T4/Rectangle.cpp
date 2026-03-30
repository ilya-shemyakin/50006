#include "Point.h"
#include "Rectangle.h"
#include <stdexcept>
#include <algorithm>

Rectangle::Rectangle(const Point& bL, const Point& tR) : bl(bL), tr(tR)
{
    if (bl.x > tr.x) std::swap(bl.x, tr.x);
    if (bl.y > tr.y) std::swap(bl.y, tr.y);
}

float Rectangle::getArea()const {
    float width = tr.x - bl.x;
    float height = tr.y - bl.y;
    return width * height;
}

Point Rectangle::getCenter()const {
    float centerX = (bl.x + tr.x)/ 2;
    float centerY = (bl.y + tr.y)/ 2;
    return Point(centerX, centerY);
}

void Rectangle::move(float x_, float y_){
    bl.x += x_;
    bl.y += y_;
    tr.x += x_;
    tr.y += y_;
}

void Rectangle::scale(float coefficient){

    if (coefficient <= 0) {
        throw std::invalid_argument("Scale coefficient must be positive");
    }

    Point center = getCenter();
    float width = tr.x - bl.x;
    float height = tr.y - bl.y;

    width *= coefficient;
    height *= coefficient;

    bl.x = center.x - width / 2;
    bl.y = center.y - height / 2;
    tr.x = center.x + width / 2;
    tr.y = center.y + height / 2;
}

const char* Rectangle::getName()const {
    return "Rectangle";
}
