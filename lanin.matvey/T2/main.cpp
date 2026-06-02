#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

static void trim(std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) {
        s.clear();
        return;
    }
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    s = s.substr(start, end - start + 1);
}

static bool parseDoubleLit(const std::string& token, double& value) {
    if (token.empty()) return false;
    char last = token.back();
    if (last != 'd' && last != 'D') return false;
    std::string numStr = token.substr(0, token.size() - 1);
    size_t dotPos = numStr.find('.');
    if (dotPos == std::string::npos) return false;
    if (dotPos == 0 || dotPos == numStr.size() - 1) return false;
    if (numStr.find('e') != std::string::npos || numStr.find('E') != std::string::npos)
        return false;
    char* endptr = nullptr;
    double v = std::strtod(numStr.c_str(), &endptr);
    if (endptr != numStr.c_str() + numStr.size()) return false;
    value = v;
    return true;
}

static bool parseLongLongLit(const std::string& token, long long& value) {
    if (token.empty()) return false;
    std::string numStr = token;
    if (numStr.size() >= 2) {
        std::string suffix = numStr.substr(numStr.size() - 2);
        if (suffix == "LL" || suffix == "ll") {
            numStr = numStr.substr(0, numStr.size() - 2);
        }
    }
    if (numStr.empty()) return false;
    if (numStr.size() > 1 && numStr[0] == '0') return false;
    if (numStr[0] == '-' && numStr.size() > 2 && numStr[1] == '0') return false;
    char* endptr = nullptr;
    long long v = std::strtoll(numStr.c_str(), &endptr, 10);
    if (endptr != numStr.c_str() + numStr.size()) return false;
    value = v;
    return true;
}

static bool parseQuotedString(const std::string& token, std::string& value) {
    if (token.size() < 2) return false;
    if (token.front() != '"' || token.back() != '"') return false;
    value = token.substr(1, token.size() - 2);
    return true;
}

static bool parseRecord(const std::string& line, DataStruct& out) {
    std::string s = line;
    trim(s);
    if (s.empty() || s.front() != '(' || s.back() != ')')
        return false;

    std::string content = s.substr(1, s.size() - 2);
    trim(content);
    if (content.empty())
        return false;

    std::vector<std::string> tokens;
    std::string cur;
    bool inQuotes = false;
    for (char c : content) {
        if (c == '"') {
            inQuotes = !inQuotes;
            cur.push_back(c);
        } else if (c == ':' && !inQuotes) {
            if (!cur.empty()) {
                tokens.push_back(cur);
                cur.clear();
            }
        } else {
            cur.push_back(c);
        }
    }
    if (!cur.empty())
        tokens.push_back(cur);

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    double k1 = 0.0;
    long long k2 = 0;
    std::string k3;

    for (const auto& token : tokens) {
        size_t spacePos = token.find(' ');
        if (spacePos == std::string::npos)
            return false;
        std::string key = token.substr(0, spacePos);
        std::string val = token.substr(spacePos + 1);
        trim(key);
        trim(val);

        if (key == "key1") {
            if (hasKey1 || !parseDoubleLit(val, k1))
                return false;
            hasKey1 = true;
        } else if (key == "key2") {
            if (hasKey2 || !parseLongLongLit(val, k2))
                return false;
            hasKey2 = true;
        } else if (key == "key3") {
            if (hasKey3 || !parseQuotedString(val, k3))
                return false;
            hasKey3 = true;
        } else {
            return false;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3)
        return false;

    out = DataStruct{k1, k2, k3};
    return true;
}

static std::string readBalancedRecord(std::istream& in) {
    char ch;
    while (in.get(ch)) {
        if (ch == '(') {
            in.putback(ch);
            break;
        }
    }
    if (!in || in.peek() != '(')
        return {};

    std::string record;
    int depth = 0;
    while (in.get(ch)) {
        record.push_back(ch);
        if (ch == '(')
            ++depth;
        else if (ch == ')') {
            --depth;
            if (depth == 0)
                break;
        }
    }
    if (depth != 0) {
        in.setstate(std::ios::failbit);
        return {};
    }
    return record;
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    while (in) {
        std::string record = readBalancedRecord(in);
        if (!in || record.empty()) {
            in.setstate(std::ios::failbit);
            return in;
        }
        DataStruct tmp;
        if (parseRecord(record, tmp)) {
            dest = tmp;
            return in;
        }
    }
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    os << "(:key1 " << std::fixed << std::setprecision(1) << ds.key1 << "d"
       << ":key2 " << ds.key2
       << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

bool compare(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.size() < b.key3.size();
}

int main() {
    std::vector<DataStruct> data;
    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));
    std::sort(data.begin(), data.end(), compare);
    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}
