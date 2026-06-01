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
            if (cmd == "RECTS") {
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

