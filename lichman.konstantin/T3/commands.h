#ifndef COMMANDS_H
#define COMMANDS_H

#include "polygon.h"

#include <iosfwd>
#include <string>
#include <vector>

struct CommandLine {
    std::string line;
};

std::istream& operator>>(std::istream& in, CommandLine& dest);

struct CommandProcessor {
    std::vector<Polygon>& polygons;

    std::string operator()(const CommandLine& commandLine) const;
};

#endif
