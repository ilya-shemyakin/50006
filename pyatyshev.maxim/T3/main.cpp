#include "polygon.hpp"
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: filename not specified" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file" << std::endl;
        return 1;
    }

    Polygons polygons;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        Polygon p;
        if (iss >> p) {
            polygons.push_back(p);
        }
    }
    file.close();

    std::cout << std::fixed << std::setprecision(1);

    std::string command;
    while (std::cin >> command) {
        if (command == "AREA") {
            std::string arg;
            std::cin >> arg;

            if (arg == "EVEN") {
                std::cout << areaSum(polygons, true) << std::endl;
            } else if (arg == "ODD") {
                std::cout << areaSum(polygons, false) << std::endl;
            } else if (arg == "MEAN") {
                if (polygons.empty()) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                } else {
                    std::cout << areaMean(polygons) << std::endl;
                }
            } else if (isValidDigit(arg)) {
                size_t n = std::stoul(arg);
                std::cout << areaByVertexCount(polygons, n) << std::endl;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }

        } else if (command == "MAX") {
            std::string arg;
            std::cin >> arg;

            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            } else if (arg == "AREA") {
                std::cout << maxArea(polygons) << std::endl;
            } else if (arg == "VERTEXES") {
                std::cout << maxVertexCount(polygons) << std::endl;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }

        } else if (command == "MIN") {
            std::string arg;
            std::cin >> arg;

            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            } else if (arg == "AREA") {
                std::cout << minArea(polygons) << std::endl;
            } else if (arg == "VERTEXES") {
                std::cout << minVertexCount(polygons) << std::endl;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }

        } else if (command == "COUNT") {
            std::string arg;
            std::cin >> arg;

            if (arg == "EVEN") {
                std::cout << countEven(polygons) << std::endl;
            } else if (arg == "ODD") {
                std::cout << countOdd(polygons) << std::endl;
            } else if (isValidDigit(arg)) {
                size_t n = std::stoul(arg);
                std::cout << countByVertexCount(polygons, n) << std::endl;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }

        } else if (command == "RECTS") {
            std::cout << rectsCount(polygons) << std::endl;

        } else if (command == "SAME") {
            std::string polyStr;
            std::string token;
            while (std::cin >> token) {
                polyStr += token;
                if (token.find(')') != std::string::npos) break;
                polyStr += " ";
            }

            Polygon target = parsePolygon(polyStr);
            if (target.vertexCount() == 0) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            } else {
                std::cout << sameCount(polygons, target) << std::endl;
            }

        } else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
