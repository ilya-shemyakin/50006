#ifndef IOFORMAT_H
#define IOFORMAT_H

#include <ios>
#include <string>

struct DelimeterIO // разделитель
{
    char exp;
};

struct DblSciIO // для чтения DBL SCI
{
    double& ref;
};

struct UllBinIO // для чтения ULL BIN (binary)
{
    unsigned long long& ref;
};

struct StringIO // для чтения строки
{
    std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
std::istream& operator>>(std::istream& in, DblSciIO&& dest);
std::istream& operator>>(std::istream& in, UllBinIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);

std::string formatDblSci(double value);
std::string formatUllBin(unsigned long long value);


#endif
