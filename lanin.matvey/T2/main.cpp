#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>

struct DataStruct {
    unsigned long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3;
};

namespace {

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool parseUllLit(const std::string& s, unsigned long long& value) {
    if (s.size() < 4) return false;
    std::string suffix = s.substr(s.size() - 3);
    if (suffix != "ull" && suffix != "ULL") return false;
    std::string numStr = s.substr(0, s.size() - 3);
    if (numStr.empty()) return false;
    for (char c : numStr) {
        if (!isDigitChar(c)) return false;
    }
    try {
        size_t pos = 0;
        unsigned long long val = std::stoull(numStr, &pos);
        if (pos != numStr.length()) return false;
        value = val;
        return true;
    } catch (...) {
        return false;
    }
}

bool parseUllBin(const std::string& s, unsigned long long& value) {
    if (s.size() < 3) return false;
    if (s[0] != '0') return false;
    if (s[1] != 'b' && s[1] != 'B') return false;
    std::string binStr = s.substr(2);
    if (binStr.empty()) return false;
    unsigned long long result = 0;
    for (char c : binStr) {
        if (c != '0' && c != '1') return false;
        if (result > (~0ULL >> 1)) return false;
        result = (result << 1) | static_cast<unsigned long long>(c - '0');
    }
    value = result;
    return true;
}

bool splitPair(const std::string& pair, std::string& key, std::string& value) {
    size_t spacePos = pair.find(' ');
    if (spacePos == std::string::npos) return false;
    if (spacePos + 1 >= pair.size()) return false;
    if (pair[spacePos + 1] == ' ') return false;
    key = pair.substr(0, spacePos);
    value = pair.substr(spacePos + 1);
    if (key.empty()) return false;
    return true;
}

bool parseDataStruct(const std::string& line, DataStruct& ds) {
    size_t start = 0;
    while (start < line.size() && (line[start] == ' ' || line[start] == '\t')) ++start;
    size_t end = line.size();
    while (end > start && (line[end - 1] == ' ' || line[end - 1] == '\t')) --end;
    if (start >= end) return false;

    std::string trimmed = line.substr(start, end - start);
    if (trimmed.size() < 2) return false;
    if (trimmed.front() != '(' || trimmed.back() != ')') return false;

    std::string content = trimmed.substr(1, trimmed.size() - 2);

    std::vector<std::string> pairs;
    size_t pos = 0;
    while (pos < content.size()) {
        if (content[pos] != ':') return false;
        ++pos;
        size_t nextColon = std::string::npos;
        bool inQuotes = false;
        for (size_t i = pos; i < content.size(); ++i) {
            if (content[i] == '"') {
                inQuotes = !inQuotes;
            } else if (content[i] == ':' && !inQuotes) {
                nextColon = i;
                break;
            }
        }
        if (inQuotes) return false;

        std::string pair;
        if (nextColon == std::string::npos) {
            pair = content.substr(pos);
            pos = content.size();
        } else {
            pair = content.substr(pos, nextColon - pos);
            pos = nextColon;
        }
        if (pair.empty()) continue;
        pairs.push_back(pair);
    }

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    unsigned long long k1 = 0, k2 = 0;
    std::string k3;

    for (const std::string& pair : pairs) {
        std::string key, value;
        if (!splitPair(pair, key, value)) return false;

        if (key == "key1") {
            if (hasKey1) return false;
            if (!parseUllLit(value, k1)) return false;
            hasKey1 = true;
        } else if (key == "key2") {
            if (hasKey2) return false;
            if (!parseUllBin(value, k2)) return false;
            hasKey2 = true;
        } else if (key == "key3") {
            if (hasKey3) return false;
            if (value.size() < 2) return false;
            if (value.front() != '"' || value.back() != '"') return false;
            k3 = value.substr(1, value.size() - 2);
            hasKey3 = true;
        } else {
            return false;
        }
    }

    if (!hasKey1 || !hasKey2 || !hasKey3) return false;

    ds.key1 = k1;
    ds.key2 = k2;
    ds.key3 = k3;
    return true;
}

} // namespace

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
    out << "(:key1 " << ds.key1 << "ull:key2 0b";
    if (ds.key2 == 0) {
        out << "0";
    } else {
        unsigned long long temp = ds.key2;
        std::string bin;
        while (temp > 0) {
            bin = char('0' + (temp & 1)) + bin;
            temp >>= 1;
        }
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
