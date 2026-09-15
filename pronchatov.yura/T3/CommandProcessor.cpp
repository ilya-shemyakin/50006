#include "CommandProcessor.hpp"
#include "Polygon.hpp"
#include "Commands.hpp"

#include <string>
#include <iostream>
#include <sstream>

namespace {
    bool parseVertexCount(const std::string& argument, std::size_t& vertexCount) {
        std::istringstream argumentStream(argument);
        int value{};

        if (!(argumentStream >> value)) {
            return false;
        }

        if (argumentStream.peek() != std::char_traits<char>::eof()) {
            return false;
        }

        if (value < 3) {
            return false;
        }

        vertexCount = static_cast<std::size_t>(value);
        return true;
    }

    bool isEndOfCommand(std::istringstream& commandStream) {
        commandStream >> std::ws;
        return commandStream.peek() == std::char_traits<char>::eof();
    }

    bool processArea(std::istringstream& commandStream, const std::vector<Polygon>& polygons) {
        std::string argument;

        if (!(commandStream >> argument)) {
            return false;
        }

        if (!(isEndOfCommand(commandStream))) {
            return false;
        }
        
        if (argument == "EVEN") {
            std::cout << calculateAreaEven(polygons) << '\n';
            return true;
        }
        if (argument == "ODD") {
            std::cout << calculateAreaOdd(polygons) << '\n';
            return true;
        }
        if (argument == "MEAN") {
            std::cout << calculateAreaMean(polygons) << '\n';
            return true;
        }
        else {
            std::size_t vertexCount;
            if (parseVertexCount(argument, vertexCount)) {
                std::cout << calculateAreaByNumberOfVertices(polygons, vertexCount) << '\n';
                return true;            
            }
            return false;
        }
    }

    bool processMax(std::istringstream& commandStream, const std::vector<Polygon>& polygons) {
        std::string argument;

        if (!(commandStream >> argument)) {
            return false;
        }

        if (!isEndOfCommand(commandStream)) {
            return false;
        }

        if (argument == "AREA") {
            std::cout << calculateMaxArea(polygons) << '\n';
            return true;
        }
        else if (argument == "VERTEXES") {
            std::cout << calculateMaxVertices(polygons) << '\n';
            return true;
        }

        return false;
    }

    bool processMin(std::istringstream& commandStream, const std::vector<Polygon>& polygons) {
        std::string argument;

        if (!(commandStream >> argument)) {
            return false;
        }
        if (!isEndOfCommand(commandStream)) {
            return false;
        }
        if (argument == "AREA") {
            std::cout << calculateMinArea(polygons) << "\n";
            return true;
        }
        if (argument == "VERTEXES") {
            std::cout << calculateMinVertices(polygons) << "\n";
            return true;
        }

        return false;
    }

    bool processCount(std::istringstream& commandStream, const std::vector<Polygon>& polygons) {
        std::string argument;

        if (!(commandStream >> argument)) {
            return false;
        }
        if (!isEndOfCommand(commandStream)) {
            return false;
        }
        if (argument == "EVEN") {
            std::cout << countEven(polygons) << '\n';
            return true;
        }
        if (argument == "ODD") {
            std::cout << countOdd(polygons) << '\n';
            return true;
        }
        
        std::size_t vertexCount;
        if (!parseVertexCount(argument, vertexCount)) {
            return false;
        }

        std::cout << countByNumberOfVertices(polygons, vertexCount) << '\n';
        return true;
    }

    bool readPolygonArgument(std::istringstream& commandStream, Polygon& polygon) {
        commandStream >> std::ws;

        if (!(commandStream >> polygon)) {
            return false;
        }
        if (!isEndOfCommand(commandStream)) {
            return false;
        }
        return true; 
    }

    bool processPerms(std::istringstream& commandStream, const std::vector<Polygon>& polygons) {
        Polygon targetPolygon;

        if (!readPolygonArgument(commandStream, targetPolygon)) {
            return false;
        }
        std::cout << countPermutations(polygons, targetPolygon) << '\n';
        
        return true;
    }

    bool processInFrame(std::istringstream& commandStream, const std::vector<Polygon>& polygons) {
        Polygon targetPolygon;

        if (!readPolygonArgument(commandStream, targetPolygon)) {
            return false;
        }

        bool result = checkInFrame(polygons, targetPolygon);

        if (result) {
            std::cout << "<TRUE>" << '\n';
        }
        else {
            std::cout << "<FALSE>" << "\n";
        }
        return true;
    }

}

bool processCommand(const std::string& commandLine, const std::vector<Polygon>& polygons) {
    std::istringstream commandStream(commandLine);
    std::string command;

    if (!(commandStream >> command)) {
        return false;
    }

    try {
        if (command == "AREA") {
            return processArea(commandStream, polygons);
        }

        if (command == "MAX") {
            return processMax(commandStream, polygons);
        }

        if (command == "MIN") {
            return processMin(commandStream, polygons);
        }

        if (command == "COUNT") {
            return processCount(commandStream, polygons);
        }

        if (command == "PERMS") {
            return processPerms(commandStream, polygons);
        }

        if (command == "INFRAME") {
            return processInFrame(commandStream, polygons);
        }
    }
    catch (const std::exception&) {
        return false;
    }

    return false;
}
