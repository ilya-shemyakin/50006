#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <functional>
#include <cctype>

struct Point {
    int x, y;
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Polygon {
    std::vector<Point> points;
    bool operator==(const Polygon& other) const {
        return points == other.points;
    }
};

static double area(const Polygon& poly) {
    if (poly.points.size() < 3) return 0.0;
    double sum = 0.0;
    size_t n = poly.points.size();
    for (size_t i = 0; i < n; ++i) {
        const Point& p1 = poly.points[i];
        const Point& p2 = poly.points[(i + 1) % n];
        sum += static_cast<double>(p1.x * p2.y - p2.x * p1.y);
    }
    return std::abs(sum) / 2.0;
}

static bool parsePolygon(const std::string& line, Polygon& poly) {
    std::istringstream iss(line);
    size_t n;
    if (!(iss >> n)) return false;
    std::vector<Point> pts;
    pts.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        char open, semicolon, close;
        int x, y;
        if (iss >> open >> x >> semicolon >> y >> close) {
            if (open == '(' && semicolon == ';' && close == ')') {
                pts.push_back({x, y});
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    if (pts.size() != n) return false;
    std::string rest;
    if (iss >> rest) return false;
    poly.points = std::move(pts);
    return true;
}

static bool parsePolygonFromTokens(const std::vector<std::string>& tokens, size_t& pos, Polygon& poly) {
    if (pos >= tokens.size()) return false;
    size_t n;
    try {
        n = std::stoul(tokens[pos++]);
    } catch (...) {
        return false;
    }
    std::vector<Point> pts;
    for (size_t i = 0; i < n; ++i) {
        if (pos >= tokens.size()) return false;
        const std::string& token = tokens[pos++];
        if (token.size() < 3 || token.front() != '(' || token.back() != ')') return false;
        size_t semicolon = token.find(';');
        if (semicolon == std::string::npos) return false;
        int x, y;
        try {
            x = std::stoi(token.substr(1, semicolon - 1));
            y = std::stoi(token.substr(semicolon + 1, token.size() - semicolon - 2));
        } catch (...) {
            return false;
        }
        pts.push_back({x, y});
    }
    if (pts.size() != n) return false;
    poly.points = std::move(pts);
    return true;
}

static std::vector<std::string> split(const std::string& s) {
    std::vector<std::string> result;
    std::istringstream iss(s);
    std::string word;
    while (iss >> word) {
        result.push_back(word);
    }
    return result;
}

static bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: no filename" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Error: cannot open file" << std::endl;
        return 1;
    }

    std::vector<Polygon> shapes;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        Polygon p;
        if (parsePolygon(line, p)) {
            shapes.push_back(p);
        }
    }

    std::string cmdLine;
    while (std::getline(std::cin, cmdLine)) {
        if (cmdLine.empty()) continue;
        auto tokens = split(cmdLine);
        if (tokens.empty()) continue;

        const std::string& command = tokens[0];

        if (command == "AREA") {
            if (tokens.size() < 2) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            const std::string& param = tokens[1];
            if (param == "EVEN") {
                double sum = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                    [](double acc, const Polygon& p) {
                        return acc + ((p.points.size() % 2 == 0) ? area(p) : 0.0);
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            } else if (param == "ODD") {
                double sum = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                    [](double acc, const Polygon& p) {
                        return acc + ((p.points.size() % 2 == 1) ? area(p) : 0.0);
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            } else if (param == "MEAN") {
                if (shapes.empty()) {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                    continue;
                }
                double total = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                    [](double acc, const Polygon& p) { return acc + area(p); });
                double mean = total / shapes.size();
                std::cout << std::fixed << std::setprecision(1) << mean << std::endl;
            } else if (isNumber(param)) {
                size_t vertexCount = std::stoul(param);
                double sum = std::accumulate(shapes.begin(), shapes.end(), 0.0,
                    [vertexCount](double acc, const Polygon& p) {
                        return acc + ((p.points.size() == vertexCount) ? area(p) : 0.0);
                    });
                std::cout << std::fixed << std::setprecision(1) << sum << std::endl;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        else if (command == "MAX") {
            if (tokens.size() < 2 || shapes.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            const std::string& param = tokens[1];
            if (param == "AREA") {
                auto it = std::max_element(shapes.begin(), shapes.end(),
                    [](const Polygon& a, const Polygon& b) {
                        return area(a) < area(b);
                    });
                if (it != shapes.end()) {
                    std::cout << std::fixed << std::setprecision(1) << area(*it) << std::endl;
                } else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            } else if (param == "VERTEXES") {
                auto it = std::max_element(shapes.begin(), shapes.end(),
                    [](const Polygon& a, const Polygon& b) {
                        return a.points.size() < b.points.size();
                    });
                if (it != shapes.end()) {
                    std::cout << it->points.size() << std::endl;
                } else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        else if (command == "MIN") {
            if (tokens.size() < 2 || shapes.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            const std::string& param = tokens[1];
            if (param == "AREA") {
                auto it = std::min_element(shapes.begin(), shapes.end(),
                    [](const Polygon& a, const Polygon& b) {
                        return area(a) < area(b);
                    });
                if (it != shapes.end()) {
                    std::cout << std::fixed << std::setprecision(1) << area(*it) << std::endl;
                } else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            } else if (param == "VERTEXES") {
                auto it = std::min_element(shapes.begin(), shapes.end(),
                    [](const Polygon& a, const Polygon& b) {
                        return a.points.size() < b.points.size();
                    });
                if (it != shapes.end()) {
                    std::cout << it->points.size() << std::endl;
                } else {
                    std::cout << "<INVALID COMMAND>" << std::endl;
                }
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        else if (command == "COUNT") {
            if (tokens.size() < 2) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            const std::string& param = tokens[1];
            if (param == "EVEN") {
                size_t cnt = std::count_if(shapes.begin(), shapes.end(),
                    [](const Polygon& p) { return p.points.size() % 2 == 0; });
                std::cout << cnt << std::endl;
            } else if (param == "ODD") {
                size_t cnt = std::count_if(shapes.begin(), shapes.end(),
                    [](const Polygon& p) { return p.points.size() % 2 == 1; });
                std::cout << cnt << std::endl;
            } else if (isNumber(param)) {
                size_t vertexCount = std::stoul(param);
                size_t cnt = std::count_if(shapes.begin(), shapes.end(),
                    [vertexCount](const Polygon& p) { return p.points.size() == vertexCount; });
                std::cout << cnt << std::endl;
            } else {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
        else if (command == "ECHO") {
            if (tokens.size() < 2) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            size_t pos = 1;
            Polygon target;
            if (!parsePolygonFromTokens(tokens, pos, target) || pos != tokens.size()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            std::vector<Polygon> newShapes;
            size_t added = 0;
            newShapes = std::accumulate(shapes.begin(), shapes.end(), std::vector<Polygon>(),
                [&target, &added](std::vector<Polygon> acc, const Polygon& p) {
                    acc.push_back(p);
                    if (p == target) {
                        acc.push_back(p);
                        ++added;
                    }
                    return acc;
                });
            shapes = std::move(newShapes);
            std::cout << added << std::endl;
        }
        else if (command == "MAXSEQ") {
            if (tokens.size() < 2) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            size_t pos = 1;
            Polygon target;
            if (!parsePolygonFromTokens(tokens, pos, target) || pos != tokens.size()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                continue;
            }
            if (shapes.empty()) {
                std::cout << 0 << std::endl;
                continue;
            }
            struct State {
                size_t current = 0;
                size_t maxLen = 0;
            };
            State init;
            State result = std::accumulate(shapes.begin(), shapes.end(), init,
                [&target](State state, const Polygon& p) {
                    if (p == target) {
                        state.current++;
                        state.maxLen = std::max(state.maxLen, state.current);
                    } else {
                        state.current = 0;
                    }
                    return state;
                });
            std::cout << result.maxLen << std::endl;
        }
        else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    }

    return 0;
}
