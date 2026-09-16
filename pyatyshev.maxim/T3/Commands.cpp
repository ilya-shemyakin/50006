#include "Commands.hpp"
#include "Functions.hpp"
#include "Polygon.hpp"
#include <iomanip>
#include <sstream>
#include <iterator>

std::vector<std::string> split(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> result;
    std::string word;

    while (iss >> word) {
        result.push_back(word);
    }

    return result;
}

void processCommands(const std::vector<Polygon>& figures) {
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        std::vector<std::string> words = split(line);
        if (words.empty()) {
            continue;
        }

        const std::string& cmd = words[0];

        try {
            if (cmd == "COUNT") {
                if (words.size() != 2) {
                    throw std::runtime_error("");
                }
                const std::string& arg = words[1];
                if (arg == "EVEN") {
                    std::cout << countEven(figures) << std::endl;
                }
                else if (arg == "ODD") {
                    std::cout << countOdd(figures) << std::endl;
                }
                else {
                    int vertexCount = std::stoi(arg);
                    if (vertexCount < 3) {
                        throw std::runtime_error("");
                    }
                    std::cout << countByVertexCount(figures, vertexCount) << std::endl;
                }
            }

            else if (cmd == "AREA") {
                if (words.size() != 2) {
                    throw std::runtime_error("");
                }

                const std::string& arg = words[1];
                std::cout << std::fixed << std::setprecision(1);

                if (arg == "EVEN") {
                    std::cout << sumAreaEven(figures) << std::endl;
                }
                else if (arg == "ODD") {
                    std::cout << sumAreaOdd(figures) << std::endl;
                }
                else if (arg == "MEAN") {
                    std::cout << meanArea(figures) << std::endl;
                }
                else {
                    int vertexCount = std::stoi(arg);
                    if (vertexCount < 3) {
                        throw std::runtime_error("");
                    }
                    std::cout << sumAreaByVertexCount(figures, vertexCount) << std::endl;
                }
            }

            else if (cmd == "MAX") {
                if (words.size() != 2) {
                    throw std::runtime_error("");
                }

                const std::string& arg = words[1];
                if (arg == "AREA") {
                    std::cout << std::fixed << std::setprecision(1) << maxArea(figures) << std::endl;
                }
                else if (arg == "VERTEXES") {
                    std::cout << maxVertexCount(figures) << std::endl;
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "MIN") {
                if (words.size() != 2) {
                    throw std::runtime_error("");
                }

                const std::string& arg = words[1];
                if (arg == "AREA") {
                    std::cout << std::fixed << std::setprecision(1) << minArea(figures) << std::endl;
                }
                else if (arg == "VERTEXES") {
                    std::cout << minVertexCount(figures) << std::endl;
                }
                else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            }

            else if (cmd == "RECTS") {
                if (words.size() != 1) {
                    throw std::runtime_error("");
                }
                std::cout << countRectangles(figures) << std::endl;
            }

            else if (cmd == "SAME") {
                if (words.size() < 2) {
                    throw std::runtime_error("");
                }


                std::string polygonStr;
                for (size_t i = 1; i < words.size(); ++i) {
                    if (i != 1) polygonStr += " ";
                    polygonStr += words[i];
                }

                Polygon target = parsePolygon(polygonStr);
                std::cout << countSameShape(figures, target) << std::endl;
            }

            else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        catch (const std::exception&) {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }
}

