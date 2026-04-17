#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <cmath>
#include <iterator>
#include <sstream>

struct DataStruct
{
    long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

double rationalMagnitude(const std::pair<long long, unsigned long long>& rat)
{
    double numerator = static_cast<double>(rat.first);
    double denominator = static_cast<double>(rat.second);
    return std::sqrt(numerator * numerator + denominator * denominator);
}

bool compareDataStruct(const DataStruct& a, const DataStruct& b)
{
    if (a.key1 != b.key1) return a.key1 < b.key1;
    double magA = rationalMagnitude(a.key2);
    double magB = rationalMagnitude(b.key2);
    if (std::abs(magA - magB) > 1e-10) return magA < magB;
    return a.key3.length() < b.key3.length();
}

bool parseSLLLit(const std::string& str, long long& value)
{
    std::string cleaned;
    for (char c : str)
        if (c != 'L' && c != 'l') cleaned += c;

    if (cleaned.empty()) return false;
    try { value = std::stoll(cleaned); return true; }
    catch (...) { return false; }
}

bool parseRATLSP(const std::string& str, std::pair<long long, unsigned long long>& value)
{
    size_t posN = str.find("(:N");
    if (posN == std::string::npos) return false;

    size_t posD = str.find(":D", posN);
    if (posD == std::string::npos) return false;

    size_t posEnd = str.find(":)", posD);
    if (posEnd == std::string::npos) return false;

    size_t numStart = posN + 3;
    while (numStart < posD && std::isspace(str[numStart])) numStart++;

    std::string numStr;
    while (numStart < posD && !std::isspace(str[numStart]) && str[numStart] != ':')
    {
        if (str[numStart] != 'L' && str[numStart] != 'l')
            numStr += str[numStart];
        numStart++;
    }

    size_t denStart = posD + 2;
    while (denStart < posEnd && std::isspace(str[denStart])) denStart++;

    std::string denStr;
    while (denStart < posEnd && !std::isspace(str[denStart]) && str[denStart] != ':')
    {
        if (str[denStart] != 'L' && str[denStart] != 'l')
            denStr += str[denStart];
        denStart++;
    }

    if (numStr.empty() || denStr.empty()) return false;

    try
    {
        long long num = std::stoll(numStr);
        unsigned long long den = std::stoull(denStr);
        if (den == 0) return false;
        value = {num, den};
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool parseQuotedString(const std::string& str, std::string& value)
{
    size_t firstQuote = str.find('"');
    if (firstQuote == std::string::npos) return false;
    size_t lastQuote = str.rfind('"');
    if (lastQuote == std::string::npos || lastQuote == firstQuote) return false;
    value = str.substr(firstQuote + 1, lastQuote - firstQuote - 1);
    return true;
}

std::istream& operator>>(std::istream& in, DataStruct& ds)
{
    std::string line;
    if (!std::getline(in, line))
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    if (line.empty())
        return in;

    if (line[0] != '(' || line.back() != ')')
        return in;

    std::string content = line.substr(1, line.length() - 2);

    bool key1Ok = false;
    bool key2Ok = false;
    bool key3Ok = false;
    DataStruct temp;

    temp.key1 = 0;
    temp.key2 = {0, 1};
    temp.key3 = "";

    size_t key1Pos = content.find("key1");
    if (key1Pos != std::string::npos)
    {
        size_t start = key1Pos + 4;
        while (start < content.length() && std::isspace(content[start])) start++;

        size_t end = start;
        while (end < content.length() && content[end] != ':') end++;

        std::string raw = content.substr(start, end - start);
        if (parseSLLLit(raw, temp.key1)) key1Ok = true;
    }

    size_t key3Pos = content.find("key3");
    if (key3Pos != std::string::npos)
    {
        size_t start = key3Pos + 4;
        while (start < content.length() && std::isspace(content[start])) start++;

        if (content[start] == '"')
        {
            size_t end = start + 1;
            while (end < content.length() && content[end] != '"') end++;

            if (end < content.length())
            {
                std::string raw = content.substr(start, end - start + 1);
                if (parseQuotedString(raw, temp.key3)) key3Ok = true;
            }
        }
    }

    size_t key2Pos = content.find("key2");
    if (key2Pos != std::string::npos)
    {
        size_t start = key2Pos + 4;
        while (start < content.length() && std::isspace(content[start])) start++;

        if (start < content.length() && content[start] == '(')
        {
            size_t end = start;
            int parenCount = 0;
            while (end < content.length())
            {
                if (content[end] == '(') parenCount++;
                if (content[end] == ')') parenCount--;
                if (parenCount == 0 && content[end] == ':' && end > start) break;
                end++;
            }

            std::string raw = content.substr(start, end - start);
            if (parseRATLSP(raw, temp.key2)) key2Ok = true;
        }
    }

    if (key1Ok && key2Ok && key3Ok)
    {
        ds = temp;
        return in;
    }

    return in;
}

std::string formatSLLLit(long long value)
{
    return std::to_string(value);
}

std::string formatRATLSP(const std::pair<long long, unsigned long long>& value)
{
    return "(:N " + std::to_string(value.first) + ":D " + std::to_string(value.second) + ":)";
}

std::string formatQuotedString(const std::string& value)
{
    return "\"" + value + "\"";
}

std::ostream& operator<<(std::ostream& os, const DataStruct& ds)
{
    os << "(:key1 " << formatSLLLit(ds.key1)
       << ":key2 " << formatRATLSP(ds.key2)
       << ":key3 " << formatQuotedString(ds.key3) << ":)";
    return os;
}

int main()
{
    std::vector<DataStruct> data;

    std::istream_iterator<DataStruct> iter(std::cin), end;
    std::copy(iter, end, std::back_inserter(data));

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::ostream_iterator<DataStruct> out_iter(std::cout, "\n");
    std::copy(data.begin(), data.end(), out_iter);

    return 0;
}
