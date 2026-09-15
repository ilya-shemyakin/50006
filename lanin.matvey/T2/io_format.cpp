#include "io_format.h"
#include <sstream>

namespace
{
  bool isDigitChar(int c)
  {
    return c >= '0' && c <= '9';
  }
}

std::istream& operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in, true); // noskipws
  if (!sentry)
  {
    return in;
  }

  char c = '\0';
  in.get(c);
  if (!in || c != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, DblLitIO&& dest)
{
  std::istream::sentry sentry(in, true); // noskipws
  if (!sentry)
  {
    return in;
  }

  std::string token;

  // Необязательный знак
  int c = in.peek();
  if (c == '+' || c == '-')
  {
    token += static_cast<char>(in.get());
  }

  // Цифры до точки (обязательно хотя бы одна)
  bool hasBefore = false;
  while (isDigitChar(in.peek()))
  {
    token += static_cast<char>(in.get());
    hasBefore = true;
  }

  // Точка обязательна
  if (in.peek() != '.')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  token += static_cast<char>(in.get());

  // Цифры после точки (обязательно хотя бы одна)
  bool hasAfter = false;
  while (isDigitChar(in.peek()))
  {
    token += static_cast<char>(in.get());
    hasAfter = true;
  }

  if (!hasBefore || !hasAfter)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  // Суффикс d / D
  c = in.peek();
  if (c != 'd' && c != 'D')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in.get();

  std::istringstream iss(token);
  double value = 0.0;
  iss >> value;
  if (!iss)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.ref = value;
  return in;
}

std::istream& operator>>(std::istream& in, SllLitIO&& dest)
{
  std::istream::sentry sentry(in, true); // noskipws
  if (!sentry)
  {
    return in;
  }

  std::string token;

  // Необязательный знак
  int c = in.peek();
  if (c == '+' || c == '-')
  {
    token += static_cast<char>(in.get());
  }

  // Хотя бы одна цифра
  bool hasDigits = false;
  while (isDigitChar(in.peek()))
  {
    token += static_cast<char>(in.get());
    hasDigits = true;
  }

  if (!hasDigits)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  // Необязательный суффикс LL / ll (регистр должен совпадать)
  c = in.peek();
  if (c == 'L' || c == 'l')
  {
    char suffix = static_cast<char>(in.get());
    if (in.peek() == suffix)
    {
      in.get();
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  std::istringstream iss(token);
  long long value = 0;
  iss >> value;
  if (!iss)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  dest.ref = value;
  return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in, true); // noskipws
  if (!sentry)
  {
    return in;
  }

  char c = '\0';
  in.get(c);
  if (!in || c != '"')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  dest.ref.clear();
  while (in.get(c))
  {
    if (c == '"')
    {
      return in;
    }
    dest.ref += c;
  }

  in.setstate(std::ios::failbit);
  return in;
}