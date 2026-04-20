#ifndef SQUARE_H
#define SQUARE_H

#include <string>

#include "shape.h"

class Square : public Shape
{
public:
	Square(const Point& center, double side);

	double getArea() const override;
	Point getCenter() const override;
	void move(double dx, double dy) override;
	void scale(double factor) override;
	std::string getName() const override;

	double getSide() const;

private:
	Point center_;
	double side_;
};

#endif