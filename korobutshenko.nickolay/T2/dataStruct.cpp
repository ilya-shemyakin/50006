#include "dataStruct.h"
#include "IOFormat.h"
#include <iomanip>
#include <sstream>

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
  if (!in)
  {
    return in;
  }

  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::istringstream iss(line);

    DataStruct temp;
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;

    iss >> DelimeterIO{ '(' };
    if (!iss)
    {
      continue;
    }

    while (!(hasKey1 && hasKey2 && hasKey3))
    {
      iss >> DelimeterIO{ ':' };
      if (!iss)
      {
        break;
      }

      std::string label;
      iss >> label;
      if (!iss)
      {
        break;
      }

      if (label == "key1" && !hasKey1)
      {
        iss >> DblLitIO{ temp.key1 };
        if (!iss)
        {
          break;
        }
        hasKey1 = true;
      }
      else if (label == "key2" && !hasKey2)
      {
        iss >> SllLitIO{ temp.key2 };
        if (!iss)
        {
          break;
        }
        hasKey2 = true;
      }
      else if (label == "key3" && !hasKey3)
      {
        iss >> StringIO{ temp.key3 };
        if (!iss)
        {
          break;
        }
        hasKey3 = true;
      }
      else
      {
        break;
      }
    }

    iss >> DelimeterIO{ ':' };
    if (!iss)
    {
      continue;
    }

    iss >> DelimeterIO{ ')' };
    if (!iss)
    {
      continue;
    }

    if (hasKey1 && hasKey2 && hasKey3 && iss)
    {
      dataStruct = temp;
      return in;
    }
  }

  in.setstate(std::ios::failbit);
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  iofguard guard(out);

  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << dataStruct.key1 << "d:";
  out << "key2 " << dataStruct.key2 << "ll:";
  out << "key3 \"" << dataStruct.key3 << "\":";
  out << ")";

  return out;
}
