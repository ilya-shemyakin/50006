#include "Point.h"
#include "Rectangle.h"

Rectangle::Rectangle(Point bL, Point tR): bl(bL), tr(tR){}


float Rectangle::getArea()const {
    float width = tr.x - bl.x;
    float height = tr.y - bl.y;
    return width * height;
}

Point Rectangle::getCenter()const {
    float centerX = (bl.x + tr.x)/ 2.0;
    float centerY = (bl.y + tr.y)/ 2.0;
    return Point(centerX, centerY);
}

void Rectangle::move(float x_, float y_){
    bl.x += x_;
    bl.y += y_;
    tr.x += x_;
    tr.y += y_;
}

void Rectangle::scale(float coefficient){
    Point center = getCenter();
    float width = tr.x - bl.x;
    float height = tr.y - bl.y;

    width *= coefficient;
    height *= coefficient;

    bl.x = center.x - width / 2.0;
    bl.y = center.y - height / 2.0;
    tr.x = center.x + width / 2.0;
    tr.y = center.y + height / 2.0;
}

const char* Rectangle::getName()const {
    return "Rectangle";
}
