#include "IO.hpp"
#include "CommandProcessor.hpp"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Filename was not specified\n";
        return 1;
    }

    try {
        std::vector<Polygon> polygons = readPolygonsFromFile(argv[1]);

        std::cout << std::fixed << std::setprecision(1);

        std::string commandLine;

        while (std::getline(std::cin, commandLine)) {
            if (!processCommand(commandLine, polygons)) {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
    }
    catch (const std::exception& exception) {
        std::cerr << exception.what() << '\n';
        return 1;
    }

    return 0;
}
