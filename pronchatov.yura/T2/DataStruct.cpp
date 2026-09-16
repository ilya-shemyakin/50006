#include "DataStruct.hpp"
#include "IOFormat.hpp"
#include <algorithm>
#include <ios>
#include <iomanip>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>

namespace {

    class StreamGuard {
    public:
        explicit StreamGuard(std::basic_ios<char>& stream):
            stream_(stream),
            precision_(stream.precision()),
            flags_(stream.flags())
        {}

        ~StreamGuard()
        {
            stream_.precision(precision_);
            stream_.flags(flags_);
        }

    private:
        std::basic_ios<char>& stream_;
        std::streamsize precision_;
        std::ios_base::fmtflags flags_;
    };

    std::string toBinaryString(unsigned long long value) {
        if (value == 0) {
            return "0";
        }

        std::string result;

        while (value > 0) {
            const char bit = static_cast<char>('0' + value % 2);
            result.push_back(bit);
            value /= 2;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    bool parseDataStruct(std::istream& in, DataStruct& dest) {
        std::istream::sentry sentry(in);

        if (!sentry) { return false; }

        DataStruct temp{}; // {} are for init

        bool hasKey1 = false;
        bool hasKey2 = false;
        bool hasKey3 = false;

        in >> DelimiterIO{'('};
        in >> DelimiterIO{':'};

        if (!in) { return false; }

        for (int i = 0; i < 3; i++) {
            std::string key;
            std::getline(in, key, ' ');
            // getline will take ' ' from the stream, but won't write it to the string
            if (key == "key1") {

                if (hasKey1) {
                    in.setstate(std::ios::failbit);
                    return false;
                }

                in >> DblSciIO{temp.key1};

                if (!in) { return false; }

                hasKey1 = true;
            }
            else if (key == "key2") {
                if (hasKey2) {
                    in.setstate(std::ios::failbit);
                    return false;
                }

                in >> UllBinIO{temp.key2};

                if (!in) { return false; }

                hasKey2 = true;
            }
            else if (key == "key3") {
                if (hasKey3) {
                    in.setstate(std::ios::failbit);
                    return false;
                }

                in >> StringIO{temp.key3};

                if (!in) { return false; }

                hasKey3 = true;
            }
            else {
                in.setstate(std::ios::failbit);
                return false;
            }

            in >> DelimiterIO{':'};

            if (!in) { return false; }
        }

        in >> DelimiterIO{')'};
        if (!in) { return false; }

        if (!hasKey1 || !hasKey2 || !hasKey3) {
            in.setstate(std::ios::failbit);
            return false;
        }

        dest = temp;

        return true;

    }

}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);

    if (!sentry) { return in; }

    std::string line;

    while (std::getline(in, line)) {
        std::istringstream lineInput(line);
        DataStruct temp{};

        if (parseDataStruct(lineInput, temp)) {
            lineInput >> std::ws;

            if (lineInput.eof()) {
                dest = temp;
                return in;
            }
        }
    }

    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data) {
    std::ostream::sentry sentry(out);

    if (!sentry) { return out; }

    StreamGuard guard(out);

    out << "(:key1 "
        << std::scientific << std::setprecision(1) << std::nouppercase
        << data.key1
        << ":key2 0b" << toBinaryString(data.key2)
        << ":key3 \"" << data.key3 << "\":)";

    return out;
}

bool DataStructComparator::operator()(
    const DataStruct& left,
    const DataStruct& right
) const {
    if (left.key1 < right.key1) {
        return true;
    }

    if (right.key1 < left.key1) {
        return false;
    }

    if (left.key2 < right.key2) {
        return true;
    }

    if (right.key2 < left.key2) {
        return false;
    }

    return left.key3.size() < right.key3.size();
}
