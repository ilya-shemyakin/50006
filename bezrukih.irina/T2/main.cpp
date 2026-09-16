#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <cctype>

struct DataStruct {
    unsigned long long key1;    
    std::complex<double> key2;  
    std::string key3;
};

static bool parseULLHex(const std::string& s, unsigned long long& out) {
    if (s.size() < 3) return false;
    if (s[0] != '0') return false;
    if (s[1] != 'x' && s[1] != 'X') return false;
    for (size_t i = 2; i < s.size(); ++i) {
        if (!std::isxdigit(static_cast<unsigned char>(s[i]))) return false;
    }
    try {
        size_t pos = 0;
        out = std::stoull(s, &pos, 16);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

static bool parseDouble(const std::string& s, double& out) {
    if (s.empty()) return false;
    try {
        size_t pos = 0;
        out = std::stod(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

static bool parseComplex(const std::string& s, std::complex<double>& out) {
    if (s.size() < 7) return false;
    if (s.substr(0, 3) != "#c(") return false;
    if (s.back() != ')') return false;

    std::string inner = s.substr(3, s.size() - 4);
    size_t spacePos = inner.find(' ');
    if (spacePos == std::string::npos) return false;

    std::string reStr = inner.substr(0, spacePos);
    std::string imStr = inner.substr(spacePos + 1);

    if (imStr.find(' ') != std::string::npos) return false;

    double re = 0, im = 0;
    if (!parseDouble(reStr, re)) return false;
    if (!parseDouble(imStr, im)) return false;

    out = std::complex<double>(re, im);
    return true;
}

static bool parseString(const std::string& s, std::string& out) {
    if (s.size() < 2) return false;
    if (s.front() != '"' || s.back() != '"') return false;
    out = s.substr(1, s.size() - 2);
    return true;
}

static bool parseLine(const std::string& line, DataStruct& ds) {
    size_t start = line.find_first_not_of(" \t\r\n");
    size_t end = line.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return false;

    std::string trimmed = line.substr(start, end - start + 1);
    if (trimmed.size() < 4) return false;
    if (trimmed.substr(0, 2) != "(:") return false;
    if (trimmed.substr(trimmed.size() - 2) != ":)") return false;

    std::string inner = trimmed.substr(2, trimmed.size() - 4);

    bool hasKey1 = false, hasKey2 = false, hasKey3 = false;
    size_t pos = 0;
    while (pos < inner.size()) {
        while (pos < inner.size() && (inner[pos] == ' ' || inner[pos] == ':')) ++pos;
        if (pos >= inner.size()) break;

        size_t nameEnd = inner.find(' ', pos);
        if (nameEnd == std::string::npos) break;
        std::string name = inner.substr(pos, nameEnd - pos);

        size_t valStart = nameEnd + 1;
        size_t valEnd = valStart;
        bool inQuotes = false;
        int depth = 0;
        while (valEnd < inner.size()) {
            char c = inner[valEnd];
            if (c == '"') inQuotes = !inQuotes;
            if (!inQuotes) {
                if (c == '(') ++depth;
                else if (c == ')') --depth;
                else if (c == ':' && depth == 0) break;
            }
            ++valEnd;
        }

        std::string value = inner.substr(valStart, valEnd - valStart);
        while (!value.empty() && value.front() == ' ') value.erase(0, 1);
        while (!value.empty() && value.back() == ' ') value.pop_back();

        if (name == "key1") {
            if (!parseULLHex(value, ds.key1)) return false;
            hasKey1 = true;
        } else if (name == "key2") {
            if (!parseComplex(value, ds.key2)) return false;
            hasKey2 = true;
        } else if (name == "key3") {
            if (!parseString(value, ds.key3)) return false;
            hasKey3 = true;
        }
        pos = valEnd;
    }
    return hasKey1 && hasKey2 && hasKey3;
}

std::istream& operator>>(std::istream& is, DataStruct& ds) {
    std::string line;
    while (std::getline(is, line)) {
        DataStruct temp;
        if (parseLine(line, temp)) {
            ds = temp;
            return is;
        }
    }
    is.setstate(std::ios::failbit);
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds) {
    os << "(:key1 0x"
       << std::uppercase << std::hex << ds.key1
       << std::dec << std::nouppercase;
    os << ":key2 #c("
       << std::fixed << std::setprecision(1)
       << ds.key2.real() << " " << ds.key2.imag() << ")";
    os << ":key3 \"" << ds.key3 << "\":)";
    return os;
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b) {
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double modA = std::abs(a.key2);
    double modB = std::abs(b.key2);
    if (modA != modB) return modA < modB;
    return a.key3.length() < b.key3.length();
}
int main() {
    std::ifstream input("input.txt");

    if (!input.is_open()) {
        std::cerr << "ERROR: Cannot open input.txt\n";
        std::cerr << "Put input.txt next to main.cpp (project folder)\n";
        std::cerr << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    std::vector<DataStruct> data;

    std::copy(std::istream_iterator<DataStruct>(input),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    std::cout << "\nPress Enter to exit...";
    std::cin.get();
    return 0;
}
