#include "composite_shape.h"
#include "rectangle.h"
#include "isosceles_trapezoid.h"
#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cmath>

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
    double total = 0.0;
    for (const auto &s : shapes_)
        total += s->getArea();
    return total;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty())
        return Point(0, 0);

    double minX = std::numeric_limits<double>::max();
    double maxX = std::numeric_limits<double>::lowest();
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::lowest();

    for (const auto &s : shapes_)
    {
        const Rectangle* rect = dynamic_cast<const Rectangle*>(s.get());
        if (rect)
        {
            minX = std::min(minX, rect->getLeft());
            maxX = std::max(maxX, rect->getRight());
            minY = std::min(minY, rect->getBottom());
            maxY = std::max(maxY, rect->getTop());
            continue;
        }

        const IsoscelesTrapezoid* trap = dynamic_cast<const IsoscelesTrapezoid*>(s.get());
        if (trap)
        {
            minX = std::min(minX, trap->getLeft());
            maxX = std::max(maxX, trap->getRight());
            minY = std::min(minY, trap->getBottom());
            maxY = std::max(maxY, trap->getTop());
            continue;
        }

        Point c = s->getCenter();
        double area = s->getArea();
        double size = std::sqrt(area);
        minX = std::min(minX, c.x - size);
        maxX = std::max(maxX, c.x + size);
        minY = std::min(minY, c.y - size);
        maxY = std::max(maxY, c.y + size);
    }

    return Point((minX + maxX) / 2.0, (minY + maxY) / 2.0);
}

void CompositeShape::move(double dx, double dy)
{
    for (auto &s : shapes_)
        s->move(dx, dy);
}

void CompositeShape::scale(double factor)
{
    Point center = getCenter();
    for (auto &s : shapes_)
    {
        Point c = s->getCenter();
        double dx = (c.x - center.x) * (factor - 1);
        double dy = (c.y - center.y) * (factor - 1);
        s->move(dx, dy);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

std::string CompositeShape::getDetails() const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < shapes_.size(); ++i)
    {
        if (i > 0)
            oss << ", ";
        const auto &s = shapes_[i];
        Point c = s->getCenter();
        oss << s->getName() << ",(" << c.x << ", " << c.y << "), " << s->getArea();
    }
    return oss.str();
}

