#include "DataStruct.hpp"
#include <sstream>
#include <cctype>
#include <algorithm>

static std::string trim(const std::string& str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

static bool parseDoubleLit(const std::string& s, double& value)
{
    std::string str = trim(s);
    if (str.empty()) {
        return false;
    }

    if (str.back() != 'd' && str.back() != 'D') {
        return false;
    }

    std::string numStr = str.substr(0, str.length() - 1);
    size_t dotPos = numStr.find('.');
    if (dotPos == std::string::npos) {
        return false;
    }
    if (dotPos == 0 || dotPos == numStr.length() - 1) {
        return false;
    }

    for (size_t i = 0; i < dotPos; ++i) {
        if (!std::isdigit(numStr[i])) {
            return false;
        }
    }
    for (size_t i = dotPos + 1; i < numStr.length(); ++i) {
        if (!std::isdigit(numStr[i])) {
            return false;
        }
    }

    std::istringstream iss(numStr);
    iss >> value;
    return !iss.fail();
}

static bool parseULLLit(const std::string& s, unsigned long long& value)
{
    std::string str = trim(s);
    if (str.empty()) {
        return false;
    }

    std::string numStr;
    if (str.length() >= 3 &&
        (str.substr(str.length() - 3) == "ULL" ||
         str.substr(str.length() - 3) == "ull")) {
        numStr = str.substr(0, str.length() - 3);
    } else if (str.length() >= 2 &&
               (str.back() == 'u' || str.back() == 'U')) {
        numStr = str.substr(0, str.length() - 1);
    } else {
        return false;
    }

    if (numStr.empty()) {
        return false;
    }

    for (char c : numStr) {
        if (!std::isdigit(c)) {
            return false;
        }
    }

    std::istringstream iss(numStr);
    iss >> value;
    return !iss.fail();
}

static bool parseField(const std::string& str, const std::string& fieldName,
                       std::string& value)
{
    std::string searchPattern = ":" + fieldName + " ";
    size_t pos = str.find(searchPattern);
    if (pos == std::string::npos) {
        return false;
    }

    size_t start = pos + searchPattern.length();
    if (start >= str.length()) {
        return false;
    }

    size_t end = str.find(':', start);
    if (end == std::string::npos) {
        return false;
    }

    value = str.substr(start, end - start);
    value = trim(value);
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
    std::string line;
    if (!std::getline(in, line)) {
        return in;
    }

    line = trim(line);

    if (line.length() < 2 || line.front() != '(' || line.back() != ')') {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::string content = line.substr(1, line.length() - 2);
    content = trim(content);

    std::string key1Str, key2Str, key3Str;
    bool hasKey1 = parseField(content, "key1", key1Str);
    bool hasKey2 = parseField(content, "key2", key2Str);
    bool hasKey3 = parseField(content, "key3", key3Str);

    if (!hasKey1 || !hasKey2 || !hasKey3) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (key3Str.length() < 2 ||
        key3Str.front() != '"' ||
        key3Str.back() != '"') {
        in.setstate(std::ios::failbit);
        return in;
    }
    data.key3 = key3Str.substr(1, key3Str.length() - 2);

    if (!parseDoubleLit(key1Str, data.key1)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (!parseULLLit(key2Str, data.key2)) {
        in.setstate(std::ios::failbit);
        return in;
    }

    return in;
}

static std::string formatDouble(double value)
{
    std::ostringstream oss;
    oss.precision(1);
    oss << std::fixed << value;
    std::string result = oss.str();

    while (result.length() > 2 && result.back() == '0') {
        result.pop_back();
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    out << "(:key1 " << formatDouble(data.key1) << "d"
        << ":key2 " << data.key2 << "ULL"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}
