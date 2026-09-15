#include "Polygon.hpp"
#include <cctype>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <stdexcept>


namespace{
    bool checkNoWhitespaceEof(std::istream& in) {
        auto next = in.peek();

        if (next == std::char_traits<char>::eof()) {
            in.setstate(std::ios::failbit);
            return false;
        }

        if (std::isspace(static_cast<unsigned char>(next))) {
            in.setstate(std::ios::failbit);
            return false;
        }

        return true;
    }

    bool readExpectedChar(std::istream& in, char expected) {
        char actual{};

        if (!in.get(actual)) {
            return false;
        }

        if (actual != expected) {
            in.setstate(std::ios::failbit);
            return false;
        }

        return true;
    }
}

std::istream& operator>>(std::istream& in, Polygon& polygon) {
    std::istream::sentry guard(in, true);

    if (!guard) {
        return in;
    }
    
    Polygon tempPolygon;
    int numberOfPoints{};
    
    if (!checkNoWhitespaceEof(in)) {
        return in;
    }

    in >> numberOfPoints;
    if (!in) {
        return in;
    }

    if (numberOfPoints < 3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    tempPolygon.points.reserve(numberOfPoints);

    for (int i = 0; i < numberOfPoints; i++) {
        char separator;
        in.get(separator);

        if (!in) {
            return in;
        }

        if (separator != ' ') {
            in.setstate(std::ios::failbit); 
            return in;
        }

        Point point;

        in >> point;
        if (!in) {
            return in;
        }

        tempPolygon.points.push_back(point);
    }

    polygon = tempPolygon;
    return in;
}

std::istream& operator>>(std::istream& in, Point& point) {
    
    std::istream::sentry guard(in, true);

    if (!guard) {
        return in;
    }

    int tempX{};
    int tempY{};

    if (!readExpectedChar(in, '(')) {
        return in;
    }

    if (!checkNoWhitespaceEof(in)) {
        return in;
    }
    
    in >> tempX;
    if (!in) {
        return in;
    }

    if (!readExpectedChar(in, ';')) {
        return in;
    }

    if (!checkNoWhitespaceEof(in)) {
        return in;
    }

    in >> tempY;
    if (!in) {
        return in;
    }

    if (!readExpectedChar(in, ')')) {
        return in;
    }
    
    point = Point{tempX, tempY};
    return in;

}

