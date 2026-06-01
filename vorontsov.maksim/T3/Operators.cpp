#include "Operators.h"
#include <algorithm>
std::istream& operator>>(std::istream& stream, Point& point) {
    std::istream::sentry sentry(stream);
    if (!sentry) {
        return stream;
    }
    StreamGuard guard(stream);
    char ch{};
    if (!stream.get(ch) || ch != '(') {
        stream.setstate(std::ios::failbit);
        return stream;
    }
    int x{};
    stream >> x;
    if (stream.fail()) {
        return stream;
    }
    if (!stream.get(ch) || ch != ';') {
        stream.setstate(std::ios::failbit);
        return stream;
    }
    int y{};
    stream >> y;
    if (stream.fail()) {
        return stream;
    }
    if (!stream.get(ch) || ch != ')') {
        stream.setstate(std::ios::failbit);
        return stream;
    }
    point.x = x;
    point.y = y;
    return stream;
}
std::istream& operator>>(std::istream& stream, Polygon& polygon) {
    std::istream::sentry sentry(stream);
    if (!sentry) {
        return stream;
    }
    StreamGuard guard(stream);
    size_t n{};
    stream >> n;
    if (stream.fail() || n < MIN_VERTICES) {
        stream.setstate(std::ios::failbit);
        return stream;
    }
    polygon.points.clear();
    polygon.points.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        Point point{};
        stream >> point;
        if (stream.fail()) {
            return stream;
        }
        polygon.points.push_back(point);
    }
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const Point& point) {
    std::ostream::sentry sentry(stream);
    if (!sentry) {
        return stream;
    }
    StreamGuard guard(stream);
    stream << "(" << point.x << ";" << point.y << ")";
    return stream;
}
std::ostream& operator<<(std::ostream& stream, const Polygon& polygon) {
    std::ostream::sentry sentry(stream);
    if (!sentry) {
        return stream;
    }
    StreamGuard guard(stream);
    stream << polygon.points.size();
    for (const auto& point : polygon.points) {
        stream << " " << point;
    }
    return stream;
}
bool operator==(const Polygon& left, const Polygon& right) {
    if (left.points.size() != right.points.size()) {
        return false;
    }
    return std::equal(left.points.begin(), left.points.end(),
        right.points.begin(),
        [](const Point& l, const Point& r) {
            return l.x == r.x && l.y == r.y;
        });
}
