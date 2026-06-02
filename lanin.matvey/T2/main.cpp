#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cctype>

struct DataStruct {
    double key1;
    long long key2;
    std::string key3;
};

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}

static std::vector<std::string> splitByColonOutsideQuotes(const std::string& s) {
    std::vector<std::string> result;
    bool inQuotes = false;
    size_t start = 0;
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '"') inQuotes = !inQuotes;
        if (!inQuotes && s[i] == ':') {
            result.push_back(s.substr(start, i - start));
            start = i + 1;
        }
    }
    result.push_back(s.substr(start));
    return result;
}

static bool parseDoubleLit(const std::string& str, double& value) {
    if (str.empty()) return false;
    std::string s = trim(str);
    if (s.length() < 2) return false;
    char last = s.back();
    if (last != 'd' && last != 'D') return false;
    std::string numStr = s.substr(0, s.length() - 1);
    size_t dotPos = numStr.find('.');
    if (dotPos == std::string::npos) return false;
    if (dotPos == 0 || dotPos == numStr.length() - 1) return false;
    try {
        size_t pos;
        double val = std::stod(numStr, &pos);
        if (pos != numStr.length()) return false;
        value = val;
        return true;
    } catch (...) {
        return false;
    }
}

static bool parseLongLongLit(const std::string& str, long long& value) {
    if (str.empty()) return false;
    std::string s = trim(str);
    if (s.length() >= 2) {
        std::string suffix = s.substr(s.length() - 2);
        if (suffix == "LL" || suffix == "Ll" || suffix == "lL" || suffix == "ll") {
            s = s.substr(0, s.length() - 2);
            if (s.empty()) return false;
        }
    }
    if (!s.empty() && s[0] == '-') {
        if (s.length() == 1) return false;
        for (size_t i = 1; i < s.length(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
        }
    } else {
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) return false;
        }
    }
    try {
        size_t pos;
        long long val = std::stoll(s, &pos);
        if (pos != s.length()) return false;
        value = val;
        return true;
    } catch (...) {
        return false;
    }
}

static bool parseQuotedString(const std::string& str, std::string& value) {
    std::string s = trim(str);
    if (s.length() < 2) return false;
    if (s.front() != '"' || s.back() != '"') return false;
    value = s.substr(1, s.length() - 2);
    return true;
}

static bool parseDataStruct(const std::string& line, DataStruct& ds) {
    std::string trimmed = trim(line);
    if (trimmed.empty() || trimmed.front() != '(' || trimmed.back() != ')')
        return false;
    std::string content = trimmed.substr(1, trimmed.length() - 2);
    std::vector<std::string> parts = splitByColonOutsideQuotes(content);
    parts.erase(std::remove_if(parts.begin(), parts.end(),
        [](const std::string& p) { return p.empty(); }), parts.end());

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    double k1 = 0.0;
    long long k2 = 0;
    std::string k3;

    for (const std::string& part : parts) {
        size_t spacePos = part.find(' ');
        if (spacePos == std::string::npos) return false;
        std::string key = trim(part.substr(0, spacePos));
        std::string value = trim(part.substr(spacePos + 1));
        if (key == "key1") {
            if (hasKey1) return false;
            if (!parseDoubleLit(value, k1)) return false;
            hasKey1 = true;
        } else if (key == "key2") {
            if (hasKey2) return false;
            if (!parseLongLongLit(value, k2)) return false;
            hasKey2 = true;
        } else if (key == "key3") {
            if (hasKey3) return false;
            if (!parseQuotedString(value, k3)) return false;
            hasKey3 = true;
        } else {
            return false;
        }
    }
    if (hasKey1 && hasKey2 && hasKey3) {
        ds.key1 = k1;
        ds.key2 = k2;
        ds.key3 = k3;
        return true;
    }
    return false;
}

std::istream& operator>>(std::istream& in, DataStruct& ds) {
    std::string line;
    while (std::getline(in, line)) {
        if (parseDataStruct(line, ds)) {
            return in;
        }
    }
    in.setstate(std::ios::failbit);
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds) {
    out << std::fixed << std::setprecision(1);
    out << "(:key1 " << ds.key1 << "d";
    out << ":key2 " << ds.key2 << "ll";
    out << ":key3 \"" << ds.key3 << "\":)";
    return out;
}

bool comparator(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    if (a.key2 != b.key2) return a.key2 < b.key2;
    return a.key3.length() < b.key3.length();
}

int main() {
    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> iter(std::cin);
    std::istream_iterator<DataStruct> end;
    std::copy(iter, end, std::back_inserter(data));
    std::sort(data.begin(), data.end(), comparator);
    std::ostream_iterator<DataStruct> outIter(std::cout, "\n");
    std::copy(data.begin(), data.end(), outIter);
    return 0;
}
