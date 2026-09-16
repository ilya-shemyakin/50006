#include "polygon.h"

#include <algorithm>
#include <cstddef>
#include <istream>

std::istream& operator>>(std::istream& in, const DelimiterIo& dest) {
    std::istream::sentry guard(in, true);
    if (guard) {
        const auto c = in.get();
        if (c != dest.exp) {
            in.setstate(std::ios::failbit);
        }
    }
    return in;
}

std::istream& operator>>(std::istream& in, Point& point) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }

    Point temp{};
    in >> DelimiterIo{'('}
        >> temp.x
        >> DelimiterIo{';'}
        >> temp.y
        >> DelimiterIo{')'};

    if (in) {
        point = temp;
    }
    return in;
}

struct PointReader {
    std::istream& in;

    Point operator()() const {
        Point point{};
        in >> DelimiterIo{' '} >> point;
        return point;
    }
};

std::istream& operator>>(std::istream& in, Polygon& polygon) {
    std::istream::sentry guard(in);
    if (!guard) {
        return in;
    }

    long long count = 0;
    in >> count;
    if (!in || count < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    Polygon temp;
    temp.points.resize(static_cast<std::size_t>(count));
    std::generate(
        temp.points.begin(),
        temp.points.end(),
        PointReader{in}
    );

    if (in) {
        polygon = temp;
    }
    return in;
}

bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator==(const Polygon& lhs, const Polygon& rhs) {
    return lhs.points == rhs.points;
}
