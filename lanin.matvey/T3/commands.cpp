#include "commands.h"

#include "methods.h"

#include <cstddef>
#include <iomanip>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>

std::istream& operator>>(std::istream& in, CommandLine& dest) {
    std::istream::sentry guard(in, true);
    if (guard) {
        std::getline(in, dest.line);
    }
    return in;
}

namespace {

bool isCommandEnd(std::istream& in) {
    in >> std::ws;
    return in.peek() == std::char_traits<char>::eof();
}

std::string processArea(
    std::istringstream& in,
    const std::vector<Polygon>& polygons
) {
    std::string argument;
    in >> argument;

    std::ostringstream out;
    out << std::fixed << std::setprecision(1);

    if (!in) {
        throw std::logic_error("Invalid command");
    }
    if (argument == "EVEN" && isCommandEnd(in)) {
        out << getAreaByParity(polygons, 0);
        return out.str();
    }
    if (argument == "ODD" && isCommandEnd(in)) {
        out << getAreaByParity(polygons, 1);
        return out.str();
    }
    if (argument == "MEAN" && isCommandEnd(in)) {
        out << getMeanArea(polygons);
        return out.str();
    }

    std::istringstream numberIn(argument);
    long long count = 0;
    numberIn >> count;
    if (
        numberIn &&
        isCommandEnd(numberIn) &&
        count >= 3 &&
        isCommandEnd(in)
    ) {
        out << getAreaByVertexCount(
            polygons,
            static_cast<std::size_t>(count)
        );
        return out.str();
    }
    throw std::logic_error("Invalid command");
}

std::string processMax(
    std::istringstream& in,
    const std::vector<Polygon>& polygons
) {
    std::string argument;
    in >> argument;
    if (!in || !isCommandEnd(in)) {
        throw std::logic_error("Invalid command");
    }

    std::ostringstream out;
    if (argument == "AREA") {
        out << std::fixed << std::setprecision(1) << getMaxArea(polygons);
        return out.str();
    }
    if (argument == "VERTEXES") {
        out << getMaxVertexCount(polygons);
        return out.str();
    }
    throw std::logic_error("Invalid command");
}

std::string processMin(
    std::istringstream& in,
    const std::vector<Polygon>& polygons
) {
    std::string argument;
    in >> argument;
    if (!in || !isCommandEnd(in)) {
        throw std::logic_error("Invalid command");
    }

    std::ostringstream out;
    if (argument == "AREA") {
        out << std::fixed << std::setprecision(1) << getMinArea(polygons);
        return out.str();
    }
    if (argument == "VERTEXES") {
        out << getMinVertexCount(polygons);
        return out.str();
    }
    throw std::logic_error("Invalid command");
}

std::string processCount(
    std::istringstream& in,
    const std::vector<Polygon>& polygons
) {
    std::string argument;
    in >> argument;
    if (!in) {
        throw std::logic_error("Invalid command");
    }
    if (argument == "EVEN" && isCommandEnd(in)) {
        return std::to_string(countByParity(polygons, 0));
    }
    if (argument == "ODD" && isCommandEnd(in)) {
        return std::to_string(countByParity(polygons, 1));
    }

    std::istringstream numberIn(argument);
    long long count = 0;
    numberIn >> count;
    if (
        numberIn &&
        isCommandEnd(numberIn) &&
        count >= 3 &&
        isCommandEnd(in)
    ) {
        return std::to_string(
            countByVertexCount(
                polygons,
                static_cast<std::size_t>(count)
            )
        );
    }
    throw std::logic_error("Invalid command");
}

std::string processEcho(
    std::istringstream& in,
    std::vector<Polygon>& polygons
) {
    in >> std::noskipws;
    Polygon polygon;
    in >> DelimiterIo{' '} >> polygon;
    if (!in || in.peek() != std::char_traits<char>::eof()) {
        throw std::logic_error("Invalid command");
    }
    return std::to_string(echoPolygon(polygons, polygon));
}

std::string processMaxSeq(
    std::istringstream& in,
    const std::vector<Polygon>& polygons
) {
    in >> std::noskipws;
    Polygon polygon;
    in >> DelimiterIo{' '} >> polygon;
    if (!in || in.peek() != std::char_traits<char>::eof()) {
        throw std::logic_error("Invalid command");
    }
    return std::to_string(maxSeq(polygons, polygon));
}

} // namespace

std::string CommandProcessor::operator()(const CommandLine& commandLine) const {
    try {
        std::istringstream in(commandLine.line);
        std::string command;
        in >> command;

        if (!in) {
            throw std::logic_error("Invalid command");
        }
        if (command == "AREA") {
            return processArea(in, polygons);
        }
        if (command == "MAX") {
            return processMax(in, polygons);
        }
        if (command == "MIN") {
            return processMin(in, polygons);
        }
        if (command == "COUNT") {
            return processCount(in, polygons);
        }
        if (command == "ECHO") {
            return processEcho(in, polygons);
        }
        if (command == "MAXSEQ") {
            return processMaxSeq(in, polygons);
        }
        throw std::logic_error("Invalid command");
    }
    catch (const std::exception&) {
        return "<INVALID COMMAND>";
    }
}
