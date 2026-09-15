#include "data_struct.h"
#include "io_format.h"

#include <sstream>
#include <iomanip>
#include <limits>

namespace
{
  std::string formatDblLit(double value)
  {
    for (int prec = 1; prec <= 350; ++prec)
    {
      std::ostringstream oss;
      oss << std::fixed << std::setprecision(prec) << value;
      const std::string text = oss.str();

      std::istringstream iss(text);
      double back = 0.0;
      iss >> back;
      if (iss && back == value)
      {
        return text;
      }
    }

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(350) << value;
    return oss.str();
  }

  bool isAlphaNumChar(int c)
  {
    return (c >= '0' && c <= '9')
        || (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z');
  }
}

bool DataStructComparator::operator()(const DataStruct& left, const DataStruct& right) const
{
  if (left.key1 != right.key1)
  {
    return left.key1 < right.key1;
  }

  if (left.key2 != right.key2)
  {
    return left.key2 < right.key2;
  }

  return left.key3.length() < right.key3.length();
}

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  double      k1 = 0.0;
  long long   k2 = 0;
  std::string k3;

  bool hasKey1 = false;
  bool hasKey2 = false;
  bool hasKey3 = false;

  in >> DelimeterIO{ '(' };
  if (!in)
  {
    return in;
  }

  while (!(hasKey1 && hasKey2 && hasKey3))
  {
    in >> DelimeterIO{ ':' };
    if (!in)
    {
      return in;
    }

    std::string label;
    int ch = in.peek();
    while (isAlphaNumChar(ch))
    {
      label += static_cast<char>(in.get());
      ch = in.peek();
    }

    if (label.empty())
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (in.peek() != ' ')
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in.get();

    if (label == "key1" && !hasKey1)
    {
      in >> DblLitIO{ k1 };
      if (!in) return in;
      hasKey1 = true;
    }
    else if (label == "key2" && !hasKey2)
    {
      in >> SllLitIO{ k2 };
      if (!in) return in;
      hasKey2 = true;
    }
    else if (label == "key3" && !hasKey3)
    {
      in >> StringIO{ k3 };
      if (!in) return in;
      hasKey3 = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  in >> DelimeterIO{ ':' };
  if (!in) return in;

  in >> DelimeterIO{ ')' };
  if (!in) return in;

  dataStruct.key1 = k1;
  dataStruct.key2 = k2;
  dataStruct.key3 = k3;

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  out << "(:key1 " << formatDblLit(dataStruct.key1) << "d:"
      << "key2 " << dataStruct.key2 << "ll:"
      << "key3 \"" << dataStruct.key3 << "\":)";

  return out;
}