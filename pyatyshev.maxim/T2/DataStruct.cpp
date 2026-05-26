#include "DataStruct.hpp"
#include <sstream>
#include <cctype>
#include <iomanip>
#include <algorithm>

static std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

static bool parseDouble(const std::string& str, double& value)
{
    if (str.length() < 2) return false;
    if (str.back() != 'd' && str.back() != 'D') return false;

    std::string numStr = str.substr(0, str.length() - 1);
    size_t dotPos = numStr.find('.');
    if (dotPos == std::string::npos) return false;
    if (dotPos == 0 || dotPos == numStr.length() - 1) return false;

    for (size_t i = 0; i < numStr.length(); ++i) {
        if (i == dotPos) continue;
        if (!std::isdigit(static_cast<unsigned char>(numStr[i]))) return false;
    }

    try {
        size_t idx = 0;
        value = std::stod(numStr, &idx);
        return idx == numStr.length();
    } catch (...) {
        return false;
    }
}

static bool parseUnsignedLongLong(const std::string& str, unsigned long long& value)
{
    if (str.length() < 4) return false;

    std::string suffix = str.substr(str.length() - 3);
    if (suffix != "ull" && suffix != "ULL") return false;

    std::string numStr = str.substr(0, str.length() - 3);
    if (numStr.empty()) return false;

    for (char c : numStr) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }

    try {
        size_t idx = 0;
        value = std::stoull(numStr, &idx);
        return idx == numStr.length();
    } catch (...) {
        return false;
    }
}

static bool parseString(const std::string& str, std::string& value)
{
    if (str.length() < 2) return false;
    if (str.front() != '"') return false;
    if (str.back() != '"') return false;

    value = str.substr(1, str.length() - 2);
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::string line;

    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (line.length() < 2 || line.front() != '(' || line.back() != ')') {
            continue;
        }

        std::string content = line.substr(1, line.length() - 2);

        bool hasKey1 = false;
        bool hasKey2 = false;
        bool hasKey3 = false;
        DataStruct temp;


        size_t pos = 0;
        while (pos < content.length()) {
            size_t colonPos = content.find(':', pos);
            if (colonPos == std::string::npos) break;

            size_t keyStart = colonPos + 1;
            size_t spacePos = content.find(' ', keyStart);
            if (spacePos == std::string::npos) break;

            std::string keyName = content.substr(keyStart, spacePos - keyStart);
            size_t valueStart = spacePos + 1;


            size_t nextColon = std::string::npos;
            std::string value;

            if (keyName == "key3") {

                size_t quoteStart = content.find('"', valueStart);
                if (quoteStart != std::string::npos) {

                    size_t quoteEnd = content.find('"', quoteStart + 1);
                    if (quoteEnd != std::string::npos) {
                        value = content.substr(quoteStart, quoteEnd - quoteStart + 1);

                        nextColon = content.find(':', quoteEnd + 1);
                    }
                }
            } else {

                nextColon = content.find(':', valueStart);
                if (nextColon != std::string::npos) {
                    value = trim(content.substr(valueStart, nextColon - valueStart));
                }
            }

            if (nextColon == std::string::npos) break;

            if (keyName == "key1") {
                if (parseDouble(value, temp.key1)) {
                    hasKey1 = true;
                }
            } else if (keyName == "key2") {
                if (parseUnsignedLongLong(value, temp.key2)) {
                    hasKey2 = true;
                }
            } else if (keyName == "key3") {
                if (parseString(value, temp.key3)) {
                    hasKey3 = true;
                }
            }

            pos = nextColon;
        }

        if (hasKey1 && hasKey2 && hasKey3) {
            data = temp;
            return in;
        }
    }

    in.setstate(std::ios::failbit);
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

