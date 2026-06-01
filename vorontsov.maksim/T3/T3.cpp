#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iomanip>
#include <cmath>
#include <limits>
#include <stdexcept>
#include "Structs.h"
#include "Operators.h"
#include "Count.h"
#include "Area.h"
#include "MaxMin.h"
#include "ECHO.h"
#include "INFRAME.h"
std::vector<std::string> parseCommand(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> words{};
    std::string word{};
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}
void processCommands(std::vector<Polygon>& polygons) {
    std::string line{};
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::vector<std::string> words = parseCommand(line);
        if (words.empty()) {
            continue;
        }
        const std::string& cmd = words[0];
        try {
            if (cmd == "COUNT") {
                if (words.size() != 2) throw std::runtime_error("");
                const std::string& arg = words[1];
                if (arg == "EVEN") {
                    std::cout << countEven(polygons) << "\n";
                } else if (arg == "ODD") {
                    std::cout << countOdd(polygons) << "\n";
                } else {
                    size_t count = static_cast<size_t>(std::stoi(arg));
                    if (count < MIN_VERTICES) throw std::runtime_error("");
                    std::cout << countByVertexCount(polygons, count) << "\n";
                }
            } else if (cmd == "AREA") {
                if (words.size() != 2) throw std::runtime_error("");
                const std::string& arg = words[1];
                if (arg == "EVEN") {
                    std::cout << sumAreaEven(polygons) << "\n";
                } else if (arg == "ODD") {
                    std::cout << sumAreaOdd(polygons) << "\n";
                } else if (arg == "MEAN") {
                    std::cout << meanArea(polygons) << "\n";
                } else {
                    size_t count = static_cast<size_t>(std::stoi(arg));
                    if (count < MIN_VERTICES) throw std::runtime_error("");
                    std::cout << sumAreaByVertexCount(polygons, count) << "\n";
                }
            } else if (cmd == "MAX") {
                if (words.size() != 2) throw std::runtime_error("");
                const std::string& arg = words[1];
                if (arg == "AREA") {
                    std::cout << maxArea(polygons) << "\n";
                } else if (arg == "VERTEXES") {
                    std::cout << maxVertexCount(polygons) << "\n";
                } else {
                    std::cout << "<INVALID COMMAND>" << "\n";
                }
            } else if (cmd == "MIN") {
                if (words.size() != 2) throw std::runtime_error("");
                const std::string& arg = words[1];
                if (arg == "AREA") {
                    std::cout << minArea(polygons) << "\n";
                } else if (arg == "VERTEXES") {
                    std::cout << minVertexCount(polygons) << "\n";
                } else {
                    std::cout << "<INVALID COMMAND>" << "\n";
                }
            } else if (cmd == "ECHO") {
                if (words.size() < 2) throw std::runtime_error("");
                std::string polygonStr = std::accumulate(
                    words.begin() + 1, words.end(), std::string(""),
                    [](const std::string& a, const std::string& b) {
                        return a.empty() ? b : a + " " + b;
                    });
                Polygon target = parsePolygon(polygonStr);
                std::cout << duplicateEcho(polygons, target) << "\n";
            } else if (cmd == "INFRAME") {
                if (words.size() < 2) throw std::runtime_error("");
                std::string polygonStr = std::accumulate(
                    words.begin() + 1, words.end(), std::string(""),
                    [](const std::string& a, const std::string& b) {
                        return a.empty() ? b : a + " " + b;
                    });
                Polygon target = parsePolygon(polygonStr);
                if (inFrame(polygons, target)) {
                    std::cout << "<TRUE>" << "\n";
                } else {
                    std::cout << "<FALSE>" << "\n";
                }
            } else {
                std::cout << "<INVALID COMMAND>" << "\n";
            }
        } catch (const std::exception&) {
            std::cout << "<INVALID COMMAND>" << "\n";
        }
    }
}
std::vector<Polygon> readShapesFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("file not found");
    }
    std::vector<Polygon> result{};
    std::string line{};
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        try {
            result.push_back(parsePolygon(line));
        } catch (...) {}
    }
    return result;
}
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Error: Invalid arguments. Usage: "
                  << argv[0] << " <filename>\n";
        return 1;
    }
    try {
        std::vector<Polygon> figures = readShapesFromFile(argv[1]);
        std::cout << std::fixed << std::setprecision(1);
        processCommands(figures);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
