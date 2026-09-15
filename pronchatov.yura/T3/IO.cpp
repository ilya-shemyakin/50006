#include "IO.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

std::vector<Polygon> readPolygonsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not find the specified file");
    }
    
    std::vector<Polygon> resultPolygonsVector;
    std::string onePolygonLine;

    while (std::getline(file, onePolygonLine)) {
        if (onePolygonLine.empty()) {
            continue;
        }

        std::istringstream onePolygonStream(onePolygonLine);
        
        Polygon polygon{};
        onePolygonStream >> polygon;
        if (!onePolygonStream) {
            continue;
        }

        if (onePolygonStream.peek() != std::char_traits<char>::eof()) {
            continue;
        }

        resultPolygonsVector.push_back(polygon);
    }

    return resultPolygonsVector;
}


