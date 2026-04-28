#include "DataStruct.hpp"
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <iomanip>


static std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

static bool parseDoubleLit(const std::string& s, double& value)
{
    std::string str = trim(s);
    if (str.empty()) return false;

    if (str.back() != 'd' && str.back() != 'D') return false;

    std::string numStr = str.substr(0, str.length() - 1);

    size_t dotPos = numStr.find('.');

    if (dotPos == std::string::npos) return false;


    std::istringstream iss(numStr);
    iss >> value;
    return !iss.fail();
}

static bool parseULLLit(const std::string& s, unsigned long long& value)
{
    std::string str = trim(s);
    if (str.empty()) return false;

    std::string numStr = str;
    if (str.length() >= 3 && (str.substr(str.length() - 3) == "ULL" ||
                               str.substr(str.length() - 3) == "ull")) {
        numStr = str.substr(0, str.length() - 3);
    } else if (str.length() >= 2 && (str.back() == 'u' || str.back() == 'U')) {
        numStr = str.substr(0, str.length() - 1);
    } else {
        return false;
    }

    if (numStr.empty()) return false;

    for (char c : numStr) {
        if (!std::isdigit(c)) return false;
    }

    std::istringstream iss(numStr);
    iss >> value;
    return !iss.fail();
}

static bool parseString(const std::string& s, std::string& value)
{
    std::string str = trim(s);
    if (str.length() < 2 || str.front() != '"' || str.back() != '"') {
        return false;
    }
    value = str.substr(1, str.length() - 2);
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::string line;
    if (!std::getline(in, line)) return in;

    line = trim(line);
    if (line.empty() || line.length() < 2 || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string content = line.substr(1, line.length() - 2);

    std::string key1Str, key2Str, key3Str;
    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    size_t pos = 0;
    while (pos < content.length()) {
        size_t colonPos = content.find(':', pos);
        if (colonPos == std::string::npos) break;
        size_t spacePos = content.find(' ', colonPos + 1);
        if (spacePos == std::string::npos) {
            spacePos = content.find(':', colonPos + 1);
            if (spacePos == std::string::npos) spacePos = content.length();
        } else {
            size_t nextColon = content.find(':', spacePos + 1);
            if (nextColon != std::string::npos && nextColon < spacePos) {
                spacePos = nextColon;
            }
        }
        if (spacePos == std::string::npos) spacePos = content.length();

        std::string fieldPart = content.substr(colonPos + 1, spacePos - colonPos - 1);
        size_t fieldSpace = fieldPart.find(' ');
        if (fieldSpace != std::string::npos) {
            std::string fieldName = fieldPart.substr(0, fieldSpace);
            std::string fieldValue = fieldPart.substr(fieldSpace + 1);
            if (fieldName == "key1") {
                hasKey1 = parseDoubleLit(fieldValue, data.key1);
            } else if (fieldName == "key2") {
                hasKey2 = parseULLLit(fieldValue, data.key2);
            } else if (fieldName == "key3") {
                hasKey3 = parseString(fieldValue, data.key3);
            }
        }
        pos = spacePos;
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
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

