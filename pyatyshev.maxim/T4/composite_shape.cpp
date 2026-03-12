#include "composite_shape.h"
#include "rectangle.h"
#include "isosceles_trapezoid.h"
#include <algorithm>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cmath>

CompositeShape::CompositeShape()
{
}

void CompositeShape::addShape(std::shared_ptr<Shape> shape)
{
    shapes_.push_back(shape);
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
        double l, r, b, t;
        bool found = false;

        auto rect = std::dynamic_pointer_cast<Rectangle>(s);
        if (rect)
        {
            l = rect->getLeft();
            r = rect->getRight();
            b = rect->getBottom();
            t = rect->getTop();
            found = true;
        }

        if (!found)
        {
            auto trap = std::dynamic_pointer_cast<IsoscelesTrapezoid>(s);
            if (trap)
            {
                l = trap->getLeft();
                r = trap->getRight();
                b = trap->getBottom();
                t = trap->getTop();
                found = true;
            }
        }

        if (!found)
        {
            Point c = s->getCenter();
            double area = s->getArea();
            double size = std::sqrt(area);
            l = c.x - size;
            r = c.x + size;
            b = c.y - size;
            t = c.y + size;
        }

        minX = std::min(minX, l);
        maxX = std::max(maxX, r);
        minY = std::min(minY, b);
        maxY = std::max(maxY, t);
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
