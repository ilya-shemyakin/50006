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

static bool isNumber(const std::string& str)
{
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(c)) return false;
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

    std::string key1Str, key2Str, key3Str;

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
            std::string value = part.substr(spacePos + 1);
            value = trim(value);

            if (name == "key1") {
                key1Str = value;
                if (value.length() > 1 && (value.back() == 'd' || value.back() == 'D')) {
                    std::string numStr = value.substr(0, value.length() - 1);
                    std::istringstream iss(numStr);
                    double val;
                    iss >> val;
                    if (!iss.fail()) {
                        data.key1 = val;
                        hasKey1 = true;
                    }
                }
            }
            else if (name == "key2") {
                key2Str = value;
                std::string numStr = value;

                if (value.length() >= 3 && (value.substr(value.length() - 3) == "ULL" || value.substr(value.length() - 3) == "ull")) {
                    numStr = value.substr(0, value.length() - 3);
                }
                else if (value.length() >= 2 && (value.back() == 'u' || value.back() == 'U')) {
                    numStr = value.substr(0, value.length() - 1);
                }

                if (isNumber(numStr)) {
                    std::istringstream iss(numStr);
                    unsigned long long val;
                    iss >> val;
                    if (!iss.fail()) {
                        data.key2 = val;
                        hasKey2 = true;
                    }
                }
            }
            else if (name == "key3") {
                key3Str = value;
                if (value.length() >= 2 && value.front() == '"' && value.back() == '"') {
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
    std::string result = oss.str();
    if (result.find('.') == std::string::npos) {
        result += ".0";
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    out << "(:key1 " << formatDouble(data.key1) << "d"
        << ":key2 " << data.key2 << "u"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

