#ifndef COMMAND_PROCESSOR_HPP
#define COMMAND_PROCESSOR_HPP

#include "Polygon.hpp"

#include <string>
#include <vector>

bool processCommand(const std::string& commandLine, const std::vector<Polygon>& polygons);

#endif
