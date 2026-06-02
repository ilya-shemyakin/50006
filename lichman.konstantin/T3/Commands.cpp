#include "Polygon.h"
#include "Commands.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No filename provided.\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Cannot open file " << argv[1] << "\n";
        return 1;
    }

    std::vector<Polygon> polys;
    std::copy(std::istream_iterator<Polygon>(file),
        std::istream_iterator<Polygon>(),
        std::back_inserter(polys));

    processCommands(polys);

    return 0;
}
