#ifndef IO_HPP
#define IO_HPP

#include "Polygon.hpp"

#include <string>
#include <vector>

std::vector<Polygon> readPolygonsFromFile(const std::string& filename);

#endif
