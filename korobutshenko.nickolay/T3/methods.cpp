#include <numeric>
#include <functional>
#include <algorithm>
#include <stdexcept>

#include "methods.h"

using namespace std::placeholders;

int getVertexCount(const Polygon& polygon)
{
  return polygon.points.size();
}

bool isEvenVertexCount(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}

bool isOddVertexCount(const Polygon& polygon)
{
  return polygon.points.size() % 2 == 1;
}

bool isVertexCount(const Polygon& polygon, int vertexCount)
{
  return polygon.points.size() == vertexCount;
}

struct accumulatorForMaxCon
{
  int first_;
  int second_;
  Polygon target_;
  accumulatorForMaxCon(int first, int second, Polygon target) : first_(first),
    second_(second), target_(target) {
  };
};

accumulatorForMaxCon f(const accumulatorForMaxCon& acc, const Polygon& p)
{
  int cur = (p == acc.target_) ? acc.second_ + 1 : 0;
  return accumulatorForMaxCon(std::max(acc.first_, cur), cur, acc.target_);
}

struct accumulatorEcho
{
  Polygon target_;
  std::vector<Polygon> result;
  accumulatorEcho(const Polygon& target) : target_(target) {};
};

accumulatorEcho fEcho(accumulatorEcho& acc, const Polygon& p)
{
  acc.result.push_back(p);
  if (p == acc.target_)
  {
    acc.result.push_back(p);
  }
  return acc;
}

int countEven(const std::vector<Polygon>& polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), isEvenVertexCount);
}

int countOdd(const std::vector<Polygon>& polygons)
{
  return std::count_if(polygons.begin(), polygons.end(), isOddVertexCount);
}

int countByVertexCount(const std::vector<Polygon>& polygons, int vertexCount)
{
  auto pred = std::bind(std::equal_to<int>(),
    std::bind(getVertexCount, _1),
    vertexCount);
  return std::count_if(polygons.begin(), polygons.end(), pred);
}

double maxArea(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::runtime_error("is empty");
  }

  auto pred = std::bind(std::less<double>(),
    std::bind(area, _1),
    std::bind(area, _2));

  auto it = std::max_element(polygons.begin(), polygons.end(), pred);
  return area(*it);
}

int maxVertexCount(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::runtime_error("is empty");
  }

  auto pred = std::bind(std::less<int>(),
    std::bind(getVertexCount, _1),
    std::bind(getVertexCount, _2));

  auto it = std::max_element(polygons.begin(), polygons.end(), pred);
  return getVertexCount(*it);
}


double minArea(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::runtime_error("is empty");
  }

  auto pred = std::bind(std::less<double>(),
    std::bind(area, _1),
    std::bind(area, _2));

  auto it = std::min_element(polygons.begin(), polygons.end(), pred);
  return area(*it);
}

int minVertexCount(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::runtime_error("is empty");
  }

  auto pred = std::bind(std::less<int>(),
    std::bind(getVertexCount, _1),
    std::bind(getVertexCount, _2));

  auto it = std::min_element(polygons.begin(), polygons.end(), pred);
  return getVertexCount(*it);
}

double sumAreaEven(const std::vector<Polygon>& polygons)
{
  auto evenArea = std::bind(std::multiplies<double>(),
    std::bind(isEvenVertexCount, _1),
    std::bind(area, _1));

  return std::accumulate(polygons.begin(), polygons.end(), 0.0,
    std::bind(std::plus<double>(), _1, std::bind(evenArea, _2)));
}

double sumAreaOdd(const std::vector<Polygon>& polygons)
{
  auto oddArea = std::bind(std::multiplies<double>(),
    std::bind(isOddVertexCount, _1),
    std::bind(area, _1));

  return std::accumulate(polygons.begin(), polygons.end(), 0.0,
    std::bind(std::plus<double>(), _1, std::bind(oddArea, _2)));
}

double sumAreaByVertexCount(const std::vector<Polygon>& polygons, int vertexCount)
{
  auto correctVertexCountArea = std::bind(std::multiplies<double>(),
    std::bind(isVertexCount, _1, _2),
    std::bind(area, _1));
  return std::accumulate(polygons.begin(), polygons.end(), 0.0,
    std::bind(std::plus<double>(), _1,
      std::bind(correctVertexCountArea, _2, vertexCount)));
}

double meanArea(const std::vector<Polygon>& polygons)
{
  if (polygons.empty())
  {
    throw std::runtime_error("is empty");
  }
  double total = std::accumulate(polygons.begin(), polygons.end(), 0.0,
    std::bind(std::plus<double>(), _1, std::bind(area, _2)));
  return total / polygons.size();
}

int maxConsecutiveEqual(const std::vector<Polygon>& polygons, const Polygon& target)
{
  auto result = std::accumulate(polygons.cbegin(), polygons.cend(),
    accumulatorForMaxCon(0, 0, target), f);
  return result.first_;
}

int duplicateEcho(const std::vector<Polygon>& polygons, const Polygon& target)
{
  auto newVector = std::accumulate(polygons.cbegin(), polygons.cend(),
    accumulatorEcho(target), fEcho);
  return newVector.result.size() - polygons.size();
}
