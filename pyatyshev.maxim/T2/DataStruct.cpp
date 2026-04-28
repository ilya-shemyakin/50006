#include "DataStruct.hpp"
#include <sstream>

#include <cctype>

#include <iomanip>
#include <cmath>

static std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

static bool isDecimalNumber(const std::string& str)
{
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::string line;
    if (!std::getline(in, line)) return in;

    line = trim(line);
    if (line.empty()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (line.length() < 2 || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string content = line.substr(1, line.length() - 2);

    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;


    size_t pos = 0;
    while (pos < content.length()) {
        size_t colonPos = content.find(':', pos);
        if (colonPos == std::string::npos) break;

        size_t nextColon = content.find(':', colonPos + 1);
        if (nextColon == std::string::npos) {
            nextColon = content.length();
        }

        std::string part = content.substr(colonPos + 1, nextColon - colonPos - 1);

        size_t spacePos = part.find(' ');
        if (spacePos != std::string::npos) {
            std::string name = part.substr(0, spacePos);
            std::string value = trim(part.substr(spacePos + 1));

            if (name == "key1") {
                if (value.length() > 2 &&
                   (value.back() == 'd' || value.back() == 'D')) {
                    std::string numStr = value.substr(0, value.length() - 1);
                    size_t dotPos = numStr.find('.');

                    if (dotPos != std::string::npos &&
                        dotPos > 0 &&
                        dotPos < numStr.length() - 1) {

                        bool valid = true;
                        for (size_t i = 0; i < numStr.length(); ++i) {
                            if (i == dotPos) continue;
                            if (!std::isdigit(static_cast<unsigned char>(numStr[i]))) {
                                valid = false;
                                break;
                            }
                        }

                        if (valid) {
                            try {
                                size_t idx = 0;
                                data.key1 = std::stod(numStr, &idx);
                                if (idx == numStr.length()) {
                                    hasKey1 = true;
                                }
                            } catch (...) {}
                        }
                    }
                }
            }
            else if (name == "key2") {
                if (value.length() >= 4) {
                    std::string suffix = value.substr(value.length() - 3);
                    if (suffix == "ull" || suffix == "ULL") {
                        std::string numStr = value.substr(0, value.length() - 3);
                        if (isDecimalNumber(numStr)) {
                            try {
                                size_t idx = 0;
                                data.key2 = std::stoull(numStr, &idx);
                                if (idx == numStr.length()) {
                                    hasKey2 = true;
                                }
                            } catch (...) {}
                        }
                    }
                }
            }
            else if (name == "key3") {
                if (value.length() >= 2 &&
                    value.front() == '"' &&
                    value.back() == '"') {
                    data.key3 = value.substr(1, value.length() - 2);
                    hasKey3 = true;
                }
            }
        }

        pos = nextColon;
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
    }

    return in;
}

static std::string formatDouble(double value)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1);
    oss << value;
    return oss.str();
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    out << "(:key1 " << formatDouble(data.key1) << "d"
        << ":key2 " << data.key2 << "ull"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}


