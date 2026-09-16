#include "IOFormat.hpp"
#include <istream>
#include <cctype> //std::isdigit
#include <sstream> //std::istringstream
#include <string>
#include <limits>

bool readTokenUntilColon(std::istream& in, std::string& token) {
    token.clear();

    while (in && in.peek() != ':') {
        char current = '\0';
        in.get(current);
        token.push_back(current);
    }
    if (!in) { return false; }
    return true;
}

bool readDigits(std::string::const_iterator& current, const std::string::const_iterator& end) {
    if (current == end || !std::isdigit(static_cast<unsigned char>(*current))) {
        return false;
    }

    while (current != end && std::isdigit(static_cast<unsigned char>(*current))) {
        ++current;
    }

    return true;
}

bool isDblSci(const std::string& token) {
    std::string::const_iterator current = token.cbegin();
    const std::string::const_iterator end = token.cend();

    if (current != end && (*current == '+' || *current == '-')) {
        ++current;
    }

    if (!readDigits(current, end)) {
        return false;
    }

    if (current == end || *current != '.') {
        return false;
    }

    ++current;

    if (!readDigits(current, end)) {
        return false;
    }

    if (current == end || (*current != 'e' && *current != 'E')) {
        return false;
    }

    ++current;

    if (current != end && (*current == '+' || *current == '-')) {
        ++current;
    }

    if (!readDigits(current, end)) {
        return false;
    }

    return current == end;
}

bool isUllBin(const std::string& token) {
    std::string::const_iterator current = token.cbegin();
    const std::string::const_iterator end = token.cend();

    if (current == end || *current != '0') {
        return false;
    }

    ++current;

    if (current == end || (*current != 'b' && *current != 'B')) {
        return false;
    }

    ++current;

    if (current == end) {
        return false;
    }

    while (current != end) {
        if (*current != '0' && *current != '1') {
            return false;
        }
        ++current;
    }

    return true;
}

bool convertUllBin (const std::string& token, unsigned long long& result) {
    std::string::const_iterator current = token.cbegin();
    const std::string::const_iterator end = token.cend();
    const unsigned long long maxValue = std::numeric_limits<unsigned long long>::max();

    if (!isUllBin(token)) {
        return false;
    }

    unsigned long long tempResult{};

    ++current;
    ++current;

    while (current != end) {
        const unsigned long long bit = static_cast<unsigned long long>(*current - '0');

        if (tempResult > (maxValue - bit) / 2) {
            return false;
        }

        tempResult = tempResult * 2 + bit;
        ++current;
    }

    result = tempResult;
    return true;
}

std::istream& operator>>(std::istream& in, DelimiterIO delimiter) {
    char current = '\0';
    in.get(current);

    if (!in) { return in; }
    if (current != delimiter.expectedChar) {
        in.setstate(std::ios::failbit);
        return in;
    }

    return in;
}


std::istream& operator>>(std::istream& in, DblSciIO dest) {

    std::string token;
    double parsedValue{};

    if (!readTokenUntilColon(in, token)){
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!isDblSci(token)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::istringstream parser(token);
    parser >> parsedValue;

    if (!parser) {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.value = parsedValue;
    return in;
}

std::istream& operator>>(std::istream& in, UllBinIO dest) {
    std::string token;
    unsigned long long parsedValue{};

    if (!readTokenUntilColon(in, token)) {
        in.setstate(std::ios::failbit);
        return in;
    }


    if (!convertUllBin(token, parsedValue)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    dest.value = parsedValue;
    return in;
}

std::istream& operator>>(std::istream& in, StringIO dest) {

    std::string parsedString;

    in >> DelimiterIO{'"'};
    if (!in) {
        return in;
    }

    std::getline(in, parsedString, '"');
    if (in.eof()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!in) {
        return in;
    }

    dest.string = parsedString;
    return in;
}
