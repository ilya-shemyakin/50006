#include <iostream>
#include <iomanip>
#include <vector>
#include "Point.h"
#include "Shape.h"
#include "Rectangle.h"
#include "Rhombus.h"
#include "CompositeShape.h"



static void printShape(std::shared_ptr<Shape> shape){
    std::cout << std::fixed << std::setprecision(2);

    if (shape->getName()== std::string("CompositeShape"))
    {
        std::shared_ptr<CompositeShape> composite = std::dynamic_pointer_cast<CompositeShape>(shape);
        Point center = composite->getCenter();
        double area = composite->getArea();

        std::cout << "[CompositeShape,(" << center.x << "," << center.y << "),"<< area << ":\n";

        for (size_t i = 0; i < composite->getShapesCount(); ++i)
        {
            std::shared_ptr<Shape> s = composite->getShape(i);
            Point c = s->getCenter();
            double a = s->getArea();
            std::cout << " " << s->getName()<< ",(" << c.x << ", " << c.y<< ")," << a;
            if (i < composite->getShapesCount()- 1)
            {
                std::cout << ",\n";
            }
        }
        std::cout << "\n]" << std::endl;
    }
    else
    {
        Point center = shape->getCenter();
        double area = shape->getArea();
        std::cout << "[" << shape->getName()<< ",(" << center.x << ","<< center.y << ")," << area << "]" << std::endl;
    }
}

int main()
{
    std::vector<std::shared_ptr<Shape>> shapes;
    auto rect1 = std::make_shared<Rectangle>(Point(0, 0), Point(4, 3));
    shapes.push_back(rect1);

    auto rect2 = std::make_shared<Rectangle>(Point(5, 5), Point(9, 8));
    shapes.push_back(rect2);

    auto rhombus1 = std::make_shared<Rhombus>(Point(10, 10), 6, 8);
    shapes.push_back(rhombus1);

    auto rhombus2 = std::make_shared<Rhombus>(Point(2, 8), 4, 5);
    shapes.push_back(rhombus2);

    auto composite = std::make_shared<CompositeShape>();
    composite->addShape(rect1);
    composite->addShape(rhombus1);
    shapes.push_back(composite);

    for(size_t i = 0; i < shapes.size(); ++i)
    {
        std::cout <<"Shape #"<<i+1<< "\nbefore" << std::endl;
        printShape(shapes[i]);
        shapes[i]->scale(2);
        std::cout << "\nafter scale" << std::endl;
        printShape(shapes[i]);
        std::cout << "\n";
    }
}
