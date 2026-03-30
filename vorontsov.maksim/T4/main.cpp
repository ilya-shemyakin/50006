#include <iostream>
#include <iomanip>
#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "CompositeShape.h"



static void printShape(const Shape& shape){

    std::cout << std::fixed << std::setprecision(2);

    if (shape.getName()== std::string("CompositeShape"))
    {

        const CompositeShape& composite = dynamic_cast<const CompositeShape&>(shape);
        Point center = composite.getCenter();
        float area = composite.getArea();

        std::cout << "[CompositeShape,(" << center.x << "," << center.y << "),"<< area << ":\n";

        for (size_t i = 0; i < composite.getShapesCount(); ++i)
        {
            const Shape & s  = composite.getShape(i);
            Point c = s.getCenter();
            float a = s.getArea();
            std::cout << " " << s.getName()<< ",(" << c.x << ", " << c.y<< ")," << a;
            if (i < composite.getShapesCount()- 1)
            {
                std::cout << ",\n";
            }
        }
        std::cout << "\n]" << std::endl;
    }
    else
    {
        Point center = shape.getCenter();
        float area = shape.getArea();
        std::cout << "[" << shape.getName()<< ",(" << center.x << ","<< center.y << ")," << area << "]" << std::endl;
    }
}

int main()
{

    std::vector<std::unique_ptr<Shape>> shapes;
    auto rect1 = std::make_unique<Rectangle>(Point(0, 0), Point(4, 3));
    shapes.push_back(std::move(rect1));

    auto rect2 = std::make_unique<Rectangle>(Point(5, 5), Point(9, 8));
    shapes.push_back(std::move(rect2));

    auto rhombus1 = std::make_unique<Rhombus>(Point(10, 10), 6, 8);
    shapes.push_back(std::move(rhombus1));

    auto rhombus2 = std::make_unique<Rhombus>(Point(2, 8), 4, 5);
    shapes.push_back(std::move(rhombus2));

    auto composite = std::make_unique<CompositeShape>();
    composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));
    composite->addShape(std::make_unique<Rhombus>(Point(10, 10), 6, 8));
    shapes.push_back((std::move(composite)));

    for(size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout <<"Shape #"<<i+1<< "\nbefore" << std::endl;
        printShape(*shapes[i]);
        shapes[i]->scale(2);
        std::cout << "\nafter scale" << std::endl;
        printShape(*shapes[i]);
        std::cout << "\n";
    }
}
