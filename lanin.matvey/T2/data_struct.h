#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iostream>

struct DataStruct
{
  double      key1 = 0.0;
  long long   key2 = 0;
  std::string key3;
};

struct DataStructComparator
{
  bool operator()(const DataStruct& left, const DataStruct& right) const;
};

std::istream& operator>>(std::istream& in, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);

#endif