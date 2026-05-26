#include "polygon.h"
#include <cmath>
#include <algorithm>
#include <sstream>
#include <fstream>

double area(const Polygon& polygon)
{
  const auto& pts = polygon.points;
  const size_t n = pts.size();
  if (n < 3)
  {
    return 0.0;
  }

  double sum = 0.0;
  for (size_t i = 0; i < n; ++i)
  {
    size_t j = (i + 1) % n;
    sum += pts[i].x * pts[j].y;
    sum -= pts[j].x * pts[i].y;
  }
  return std::abs(sum) / 2.0;
}

bool operator==(const Polygon& left, const Polygon& right)
{
  if (left.points.size() != right.points.size())
  {
    return false;
  }
  return std::equal(left.points.begin(), left.points.end(), right.points.begin(),
    [](const Point& left, const Point& right) {
      return left.x == right.x && left.y == right.y;
    });
}

Polygon parsePolygon(const std::string& string)
{
  std::istringstream iss(string);
  size_t n;
  iss >> n;

  if (iss.fail())
  {
    throw std::runtime_error("invalid data for vertex count");
  }

  if (n < 3)
  {
    throw std::runtime_error("polygon must have more than 2 vertises");
  }

  size_t numberOfWS = 0;
  for (size_t i = 0; i < string.length(); ++i)
  {
    if (string[i] == ' ')
    {
      ++numberOfWS;
    }
  }

  if (numberOfWS != n)
  {
    throw std::runtime_error("incorrect enter");
  }

  Polygon polygon;

  for (size_t i = 0; i < n; ++i)
  {
    char open, sep, close;
    int x, y;
    iss >> open >> x >> sep >> y >> close;
    if (iss.fail() || open != '(' || sep != ';' || close != ')')
    {
      throw std::runtime_error("invalid format");
    }
    polygon.points.push_back({ x,y });
  }

  char leftover;
  if (iss >> leftover)
  {
    throw std::runtime_error("extra character");
  }

  return polygon;
}

std::vector<Polygon> readShapesFromFile(const std::string& filename)
{
  std::fstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("have not found file");
  }

  std::vector<Polygon> result;
  std::string line;
  while (std::getline(file, line))
  {
    if (line.empty())
    {
      continue;
    }
    try
    {
      result.push_back(parsePolygon(line));
    }
    catch (...) {}
  }
  return result;
}
