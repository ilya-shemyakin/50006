#include "commands.h"
#include "methods.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Filename is not specified\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    std::vector<Polygon> polygons = readPolygons(file);
    std::transform(
        std::istream_iterator<CommandLine>(std::cin),
        std::istream_iterator<CommandLine>(),
        std::ostream_iterator<std::string>(std::cout, "\n"),
        CommandProcessor{polygons}
    );

    return 0;
}
