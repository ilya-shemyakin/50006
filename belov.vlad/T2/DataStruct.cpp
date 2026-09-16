#include <cctype>
#include <iomanip>
#include <ios>
#include <string>

#include "DataStruct.h"
#include "StreamGuard.h"

namespace {
    bool readExpected(std::istream& stream, char expected) {
        char ch{};
        if (!stream.get(ch) || ch != expected) {
            stream.setstate(std::ios::failbit);
            return false;
        }
        return true;
    }

    bool readCharLiteral(std::istream& stream, char& value) {
        if (!readExpected(stream, '\'')) {
            return false;
        }

        if (!stream.get(value)) {
            stream.setstate(std::ios::failbit);
            return false;
        }

        if (!readExpected(stream, '\'')) {
            return false;
        }

        return true;
    }

    bool readRational(std::istream& stream,
        std::pair<long long, unsigned long long>& value) {
        if (!readExpected(stream, '(')) {
            return false;
        }

        if (!readExpected(stream, ':')) {
            return false;
        }

        char ch{};

        if (!stream.get(ch) || ch != 'N') {
            stream.setstate(std::ios::failbit);
            return false;
        }

        if (!readExpected(stream, ' ')) {
            return false;
        }

        long long numerator{};
        stream >> numerator;

        if (stream.fail()) {
            return false;
        }

        if (!readExpected(stream, ':')) {
            return false;
        }

        if (!readExpected(stream, 'D')) {
            return false;
        }

        if (!readExpected(stream, ' ')) {
            return false;
        }

        unsigned long long denominator{};
        stream >> denominator;

        if (stream.fail() || denominator == 0) {
            stream.setstate(std::ios::failbit);
            return false;
        }

        if (!readExpected(stream, ':')) {
            return false;
        }

        if (!readExpected(stream, ')')) {
            return false;
        }

        value = { numerator, denominator };
        return true;
    }
}

std::istream& operator>>(std::istream& stream, DataStruct& data) {
    std::istream::sentry sentry(stream);

    if (!sentry) {
        return stream;
    }

    StreamGuard guard(stream);

    if (!readExpected(stream, '(') ||
        !readExpected(stream, ':')) {
        return stream;
    }

    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    while (true) {
        const int next = stream.peek();

        if (next == ')') {
            stream.get();
            break;
        }

        if (next == std::char_traits<char>::eof() ||
            std::isspace(static_cast<unsigned char>(next))) {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        std::string fieldName;
        stream >> fieldName;

        if (stream.fail() || fieldName.empty()) {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        if (!readExpected(stream, ' ')) {
            return stream;
        }

        if (fieldName == "key1") {
            char value{};

            if (!readCharLiteral(stream, value)) {
                return stream;
            }

            data.key1 = value;
            hasKey1 = true;
        }
        else if (fieldName == "key2") {
            std::pair<long long, unsigned long long> value{};

            if (!readRational(stream, value)) {
                return stream;
            }

            data.key2 = value;
            hasKey2 = true;
        }
        else if (fieldName == "key3") {
            if (!readExpected(stream, '"')) {
                return stream;
            }

            std::getline(stream, data.key3, '"');

            if (stream.fail()) {
                return stream;
            }

            hasKey3 = true;
        }
        else {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        const int separator = stream.peek();
        if (separator == std::char_traits<char>::eof() ||
            std::isspace(static_cast<unsigned char>(separator))) {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        if (!readExpected(stream, ':')) {
            return stream;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        stream.setstate(std::ios::failbit);
    }

    return stream;
}

std::ostream& operator<<(std::ostream& stream,
    const DataStruct& data) {
    std::ostream::sentry sentry(stream);

    if (sentry) {
        StreamGuard guard(stream);

        stream << "(:key1 '"
            << data.key1
            << "':key2 (:N "
            << data.key2.first
            << ":D "
            << data.key2.second
            << ":):key3 \""
            << data.key3
            << "\":)";
    }

    return stream;
}
