#ifndef IOFORMAT_HPP
#define IOFORMAT_HPP

#include "DataStruct.hpp"
#include <string>
#include <istream>

struct DelimiterIO {
    char expectedChar;
};

struct DblSciIO {
    double& value;
};

struct UllBinIO {
    unsigned long long& value;
};

struct StringIO {
    std::string& string;
};

std::istream& operator>>(std::istream& in, DelimiterIO delimiter);
std::istream& operator>>(std::istream& in, DblSciIO dest);
std::istream& operator>>(std::istream& in, UllBinIO dest);
std::istream& operator>>(std::istream& in, StringIO dest);


#endif
