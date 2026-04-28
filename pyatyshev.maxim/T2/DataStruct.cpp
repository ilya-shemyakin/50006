#include "DataStruct.hpp"
#include <sstream>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>

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
    if (str.empty()) return false;

    if (str.back() != 'd' && str.back() != 'D') return false;

    std::string numStr = str.substr(0, str.length() - 1);

    size_t dotPos = numStr.find('.');
    if (dotPos == std::string::npos) return false;
    if (dotPos == 0 || dotPos == numStr.length() - 1) return false;

    for (size_t i = 0; i < dotPos; ++i) {
        if (!std::isdigit(numStr[i])) return false;
    }
    for (size_t i = dotPos + 1; i < numStr.length(); ++i) {
        if (!std::isdigit(numStr[i])) return false;
    }

    std::istringstream iss(numStr);
    iss >> value;
    return !iss.fail();
}

static bool parseULLLit(const std::string& s, unsigned long long& value)
{
    std::string str = trim(s);
    if (str.empty()) return false;

    std::string numStr = str;

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

    if (numStr.empty()) return false;

    for (char c : numStr) {
        if (!std::isdigit(c)) return false;
    }

    std::istringstream iss(numStr);
    iss >> value;
    return !iss.fail();
}

static void splitFields(const std::string& content,
                        std::vector<std::pair<std::string, std::string>>& fields)
{
    size_t pos = 0;
    while (pos < content.length()) {
        size_t colonPos = content.find(':', pos);
        if (colonPos == std::string::npos) break;

        size_t nextColon = content.find(':', colonPos + 1);
        if (nextColon == std::string::npos) {
            nextColon = content.length();
        }

        std::string fieldValue = content.substr(colonPos + 1, nextColon - colonPos - 1);

        size_t spacePos = fieldValue.find(' ');
        if (spacePos != std::string::npos) {
            std::string fieldName = fieldValue.substr(0, spacePos);
            std::string value = fieldValue.substr(spacePos + 1);
            fields.push_back({fieldName, value});
        } else {
            fields.push_back({"", ""});
        }

        pos = nextColon;
    }
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
    content = trim(content);

    std::vector<std::pair<std::string, std::string>> fields;
    splitFields(content, fields);

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;

    for (const auto& field : fields) {
        const std::string& name = field.first;
        const std::string& value = field.second;

        if (name == "key1") {
            if (parseDoubleLit(value, data.key1)) {
                hasKey1 = true;
            }
        } else if (name == "key2") {
            if (parseULLLit(value, data.key2)) {
                hasKey2 = true;
            }
        } else if (name == "key3") {
            std::string trimmedValue = trim(value);
            if (trimmedValue.length() >= 2 &&
                trimmedValue.front() == '"' &&
                trimmedValue.back() == '"') {
                data.key3 = trimmedValue.substr(1, trimmedValue.length() - 2);
                hasKey3 = true;
            }
        }
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
    return oss.str();
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    out << "(:key1 " << formatDouble(data.key1) << "d"
        << ":key2 " << data.key2 << "u"
        << ":key3 \"" << data.key3 << "\":)";
    return out;
}

