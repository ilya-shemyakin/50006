#ifndef IO_FORMAT_H
#define IO_FORMAT_H

#include <string>
#include <iostream>

struct DelimeterIO
{
  char exp;
};

struct DblLitIO
{
  double& ref;
};

struct SllLitIO
{
  long long& ref;
};

struct StringIO
{
  std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
std::istream& operator>>(std::istream& in, DblLitIO&& dest);
std::istream& operator>>(std::istream& in, SllLitIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);

#endif