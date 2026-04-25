#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iosfwd>
#include <string>
#include <complex>

struct DataStruct {
    unsigned long long key1_;
    std::complex<double> key2_;
    std::string key3_;
};

std::istream& operator>>(std::istream& is, DataStruct& data);
std::ostream& operator<<(std::ostream& os, const DataStruct& data);


#endif
