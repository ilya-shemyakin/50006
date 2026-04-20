#include "compositeShape.h"

#include <stdexcept>

#include "rectangle.h"
#include "square.h"

void CompositeShape::addShape(std::unique_ptr<Shape> shape)
{
    if (!shape)
    {
        throw std::invalid_argument("Null shape");
    }

    if (dynamic_cast<CompositeShape*>(shape.get()))
    {
        throw std::invalid_argument("Nested composite forbidden");
    }

    shapes_.push_back(std::move(shape));
}

double CompositeShape::getArea() const
{
    double sum = 0.0;

    for (const auto& s : shapes_)
    {
        sum += s->getArea();
    }

    return sum;
}

Point CompositeShape::getCenter() const
{
    if (shapes_.empty())
    {
        throw std::logic_error("Empty composite");
    }

    bool first = true;
    double minX, maxX, minY, maxY;

    for (const auto& s : shapes_)
    {
        if (const Rectangle* r = dynamic_cast<const Rectangle*>(s.get()))
        {
            Point bl = r->getBottomLeft();
            Point tr = r->getTopRight();

            if (first)
            {
                minX = bl.x; maxX = tr.x;
                minY = bl.y; maxY = tr.y;
                first = false;
            }
            else
            {
                if (bl.x < minX) minX = bl.x;
                if (tr.x > maxX) maxX = tr.x;
                if (bl.y < minY) minY = bl.y;
                if (tr.y > maxY) maxY = tr.y;
            }
        }
        else if (const Square* sq = dynamic_cast<const Square*>(s.get()))
        {
            Point c = sq->getCenter();
            double h = sq->getSide() / 2.0;

            double left = c.x - h;
            double right = c.x + h;
            double bottom = c.y - h;
            double top = c.y + h;

            if (first)
            {
                minX = left; maxX = right;
                minY = bottom; maxY = top;
                first = false;
            }
            else
            {
                if (left < minX) minX = left;
                if (right > maxX) maxX = right;
                if (bottom < minY) minY = bottom;
                if (top > maxY) maxY = top;
            }
        }
    }

    return { (minX + maxX) / 2.0, (minY + maxY) / 2.0 };
}

void CompositeShape::move(double dx, double dy)
{
    for (auto& s : shapes_)
    {
        s->move(dx, dy);
    }
}

void CompositeShape::scale(double factor)
{
    if (factor <= 0.0)
    {
        throw std::invalid_argument("Invalid scale");
    }

    Point c = getCenter();

    for (auto& s : shapes_)
    {
        Point sc = s->getCenter();

        double dx = (sc.x - c.x) * (factor - 1.0);
        double dy = (sc.y - c.y) * (factor - 1.0);

        s->move(dx, dy);
        s->scale(factor);
    }
}

std::string CompositeShape::getName() const
{
    return "COMPOSITE";
}

const std::vector<std::unique_ptr<Shape>>&
CompositeShape::getShapes() const
{
    return shapes_;
}