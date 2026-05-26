#ifndef POINT_H
#define POINT_H

struct Point {
    double x;
    double y;

    Point(double xCoordinate, double yCoordinate)
        : x(xCoordinate), y(yCoordinate) {
    }

};

#endif
