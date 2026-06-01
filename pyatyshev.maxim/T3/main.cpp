#include "Polygon.hpp"
#include "Commands.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    try {
        std::vector<Polygon> figures = readShapesFromFile(argv[1]);
        processCommands(figures);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


