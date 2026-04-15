#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cctype>

struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
};

bool parseUllLit(const std::string& s, unsigned long long& value) {
    if (s.empty()) return false;
    size_t len = s.length();
    if (len < 3) return false;
    std::string suffix = s.substr(len - 3);
    if (suffix != "ull" && suffix != "ULL") return false;
    std::string numStr = s.substr(0, len - 3);
    if (numStr.empty()) return false;
    for (char c : numStr) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    try {
        size_t pos;
        unsigned long long val = std::stoull(numStr, &pos);
        if (pos != numStr.length()) return false;
        value = val;
        return true;
    }
    catch (...) {
        return false;
    }
}

bool parseUllBin(const std::string& s, unsigned long long& value) {
    if (s.empty()) return false;
    if (s.length() < 3) return false;
    if (!(s[0] == '0' && (s[1] == 'b' || s[1] == 'B'))) return false;
    std::string binStr = s.substr(2);
    if (binStr.empty()) return false;
    unsigned long long result = 0;
    for (char c : binStr) {
        if (c != '0' && c != '1') return false;
        result = (result << 1) | (c - '0');
    }
    value = result;
    return true;
}

bool parseDataStruct(const std::string& line, DataStruct& ds) {
    size_t start = line.find_first_not_of(" \t");
    if (start == std::string::npos) return false;
    size_t end = line.find_last_not_of(" \t");
    std::string trimmed = line.substr(start, end - start + 1);

    if (trimmed.empty() || trimmed.front() != '(' || trimmed.back() != ')') return false;
    std::string content = trimmed.substr(1, trimmed.size() - 2);

    std::vector<std::string> pairs;
    size_t pos = 0;
    while (pos < content.size()) {
        if (content[pos] != ':') return false;
        pos++;
        size_t nextColon = content.find(':', pos);
        std::string pair;
        if (nextColon == std::string::npos) {
            pair = content.substr(pos);
            pos = content.size();
        }
        else {
            pair = content.substr(pos, nextColon - pos);
            pos = nextColon;
        }
        if (pair.empty()) continue;
        pairs.push_back(pair);
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    unsigned long long k1 = 0, k2 = 0;
    std::string k3;

    for (const auto& pair : pairs) {
        size_t spacePos = pair.find(' ');
        if (spacePos == std::string::npos) return false;
        std::string key = pair.substr(0, spacePos);
        std::string value = pair.substr(spacePos + 1);
        if (key == "key1") {
            if (hasKey1) return false;
            if (!parseUllLit(value, k1)) return false;
            hasKey1 = true;
        }
        else if (key == "key2") {
            if (hasKey2) return false;
            if (!parseUllBin(value, k2)) return false;
            hasKey2 = true;
        }
        else if (key == "key3") {
            if (hasKey3) return false;
            if (value.size() < 2 || value.front() != '"' || value.back() != '"') return false;
            k3 = value.substr(1, value.size() - 2);
            hasKey3 = true;
        }
        else {
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
    out << "(:key1 " << ds.key1 << "ull"
        << ":key2 0b";

    if (ds.key2 == 0) {
        out << "0";
    }
    else {
        unsigned long long temp = ds.key2;
        std::string bin;
        while (temp) {
            bin.push_back((temp & 1) ? '1' : '0');
            temp >>= 1;
        }
        std::reverse(bin.begin(), bin.end());
        out << bin;
    }
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