#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <stdexcept>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Shape {
public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void scale(double factor) = 0;
    virtual std::string getName() const = 0;

    virtual void print(std::ostream& os) const {
        os << std::fixed << std::setprecision(2)
            << getName() << ", ("
            << getCenter().x << ", "
            << getCenter().y << "), "
            << getArea();
    }

    friend std::ostream& operator<<(std::ostream& os, const Shape& s) {
        s.print(os);
        return os;
    }
};

class Rectangle : public Shape {
private:
    Point left_bottom;
    Point right_top;

public:
    Rectangle(const Point& lb, const Point& rt)
        : left_bottom(lb), right_top(rt) {
        if (lb.x >= rt.x || lb.y >= rt.y) {
            throw std::invalid_argument("Invalid rectangle coordinates");
        }
    }

    double getArea() const override {
        return (right_top.x - left_bottom.x) * (right_top.y - left_bottom.y);
    }

    Point getCenter() const override {
        return Point((left_bottom.x + right_top.x) / 2.0,
            (left_bottom.y + right_top.y) / 2.0);
    }

    void move(double dx, double dy) override {
        left_bottom.x += dx;
        left_bottom.y += dy;
        right_top.x += dx;
        right_top.y += dy;
    }

    void scale(double factor) override {
        if (factor <= 0) throw std::invalid_argument("Factor must be positive");
        Point c = getCenter();
        left_bottom.x = c.x + (left_bottom.x - c.x) * factor;
        left_bottom.y = c.y + (left_bottom.y - c.y) * factor;
        right_top.x = c.x + (right_top.x - c.x) * factor;
        right_top.y = c.y + (right_top.y - c.y) * factor;
    }

    std::string getName() const override { return "RECTANGLE"; }
};

class Ring : public Shape {
private:
    Point center;
    double outer_radius;
    double inner_radius;

public:
    Ring(const Point& c, double outer_r, double inner_r)
        : center(c), outer_radius(outer_r), inner_radius(inner_r) {
        if (outer_r <= 0 || inner_r < 0 || inner_r >= outer_r) {
            throw std::invalid_argument("Invalid ring radii");
        }
    }

    double getArea() const override {
        return M_PI * (outer_radius * outer_radius - inner_radius * inner_radius);
    }

    Point getCenter() const override { return center; }

    void move(double dx, double dy) override {
        center.x += dx;
        center.y += dy;
    }

    void scale(double factor) override {
        if (factor <= 0) throw std::invalid_argument("Factor must be positive");
        outer_radius *= factor;
        inner_radius *= factor;
    }

    std::string getName() const override { return "RING"; }
};

class CompositeShape : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;

public:
    CompositeShape() = default;

    CompositeShape(const CompositeShape&) = delete;
    CompositeShape& operator=(const CompositeShape&) = delete;

    CompositeShape(CompositeShape&&) noexcept = default;
    CompositeShape& operator=(CompositeShape&&) noexcept = default;

    ~CompositeShape() override = default;

    void addShape(std::unique_ptr<Shape> shape) {
        if (!shape) throw std::invalid_argument("Cannot add null shape");
        shapes.push_back(std::move(shape));
    }

    double getArea() const override {
        double total = 0.0;
        for (const auto& s : shapes) total += s->getArea();
        return total;
    }

    Point getCenter() const override {
        if (shapes.empty()) return Point(0, 0);

        double min_x = std::numeric_limits<double>::max();
        double min_y = std::numeric_limits<double>::max();
        double max_x = -std::numeric_limits<double>::max();
        double max_y = -std::numeric_limits<double>::max();

        for (const auto& s : shapes) {
            Point c = s->getCenter();
            min_x = (std::min)(min_x, c.x);
            min_y = (std::min)(min_y, c.y);
            max_x = (std::max)(max_x, c.x);
            max_y = (std::max)(max_y, c.y);
        }
        return Point((min_x + max_x) / 2.0, (min_y + max_y) / 2.0);
    }

    void move(double dx, double dy) override {
        for (auto& s : shapes) s->move(dx, dy);
    }

    void scale(double factor) override {
        if (factor <= 0) throw std::invalid_argument("Factor must be positive");
        Point center = getCenter();
        for (auto& s : shapes) {
            Point c = s->getCenter();
            double dx = (c.x - center.x) * (factor - 1.0);
            double dy = (c.y - center.y) * (factor - 1.0);
            s->move(dx, dy);
            s->scale(factor);
        }
    }

    std::string getName() const override { return "COMPOSITE"; }

    void print(std::ostream& os) const override {
        os << std::fixed << std::setprecision(2)
            << getName() << ", (" << getCenter().x << ", "
            << getCenter().y << "), " << getArea() << ":\n";
        for (size_t i = 0; i < shapes.size(); ++i) {
            os << "  ";
            shapes[i]->print(os);
            if (i != shapes.size() - 1) os << ",\n";
        }
    }
};

int main() {
    try {
        std::vector<std::unique_ptr<Shape>> shapes;

        shapes.push_back(std::make_unique<Rectangle>(Point(0, 0), Point(4, 3)));

        shapes.push_back(std::make_unique<Ring>(Point(5, 5), 3.0, 1.0));

        shapes.push_back(std::make_unique<Rectangle>(Point(-2, -2), Point(1, 1)));

        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point(0, 0), Point(2, 2)));
        composite->addShape(std::make_unique<Ring>(Point(3, 3), 1.5, 0.5));
        shapes.push_back(std::move(composite));

        shapes.push_back(std::make_unique<Ring>(Point(-3, -3), 2.0, 0.5));

        std::cout << "=== Before scaling ===\n";
        for (const auto& s : shapes) {
            s->print(std::cout);
            std::cout << "\n";
        }

        for (auto& s : shapes) s->scale(2.0);

        std::cout << "\n=== After scaling (x2) ===\n";
        for (const auto& s : shapes) {
            s->print(std::cout);
            std::cout << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
