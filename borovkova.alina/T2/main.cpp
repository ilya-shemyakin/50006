#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
struct DataStruct
{
    double key1;
    char key2;
    std::string key3;
};

bool isDigits(const std::string& text, std::size_t begin, std::size_t end)
{
    if (begin == end)
    {
        return false;
    }
    for (std::size_t i = begin; i < end; ++i)
    {
        if (!std::isdigit(static_cast<unsigned char>(text[i])))
        {
            return false;
        }
    }
    return true;
}
bool parseScientific(const std::string& text, double& value)
{
    const std::size_t ePos = text.find_first_of("eE");
    if (ePos == std::string::npos || text.find_first_of("eE", ePos + 1) != std::string::npos)
    {
        return false;
    }

    std::size_t mantissaBegin = 0;
    if (mantissaBegin < ePos && (text[mantissaBegin] == '+' || text[mantissaBegin] == '-'))
    {
        ++mantissaBegin;
    }

    const std::size_t dotPos = text.find('.', mantissaBegin);
    if (dotPos == std::string::npos || dotPos >= ePos)
    {
        return false;
    }

    if (!isDigits(text, mantissaBegin, dotPos))
    {
        return false;
    }

    if (!isDigits(text, dotPos + 1, ePos))
    {
        return false;
    }

    std::size_t exponentBegin = ePos + 1;
    if (exponentBegin < text.size() && (text[exponentBegin] == '+' || text[exponentBegin] == '-'))
    {
        ++exponentBegin;
    }
    if (!isDigits(text, exponentBegin, text.size()))
    {
        return false;
    }

    std::istringstream numberStream(text);
    numberStream >> value;
    if (!numberStream)
    {
        return false;
    }
    numberStream >> std::ws;
    return numberStream.eof();          
}

bool parseLine(const std::string& source, DataStruct& result)
{
    std::size_t first = 0;
    while (first < source.size() && std::isspace(static_cast<unsigned char>(source[first])))
    {
        ++first;
    }

    std::size_t last = source.size();
    while (last > first && std::isspace(static_cast<unsigned char>(source[last - 1])))
    {
        --last;
    }

    const std::string line = source.substr(first, last - first);
    if (line.size() < 4 || line.front() != '(' || line.back() != ')')
    {
        return false;
    }

    DataStruct temp{};
    bool hasKey1 = false;
    bool hasKey2 = false;
    bool hasKey3 = false;
    std::size_t pos = 1;
    while (pos < line.size() - 1)
    {
        if (line[pos] != ':')
        {
            return false;
        }
        if (pos + 1 == line.size() - 1)
        {
            break;
        }
        if (line.compare(pos, 6, ":key1 ") == 0)
        {
            if (hasKey1)
            {
                return false;
            }
            pos += 6;
            const std::size_t end = line.find(':', pos);
            if (end == std::string::npos)
            {
                return false;
            }
            const std::string number = line.substr(pos, end - pos);
            if (!parseScientific(number, temp.key1))
            {
                return false;
            }
            hasKey1 = true;
            pos = end;
        }
        else if (line.compare(pos, 6, ":key2 ") == 0)
        {
            if (hasKey2)
            {
                return false;
            }
            pos += 6;
            if (pos + 2 >= line.size() || line[pos] != '\'' || line[pos + 2] != '\'')
            {
                return false;
            }
            temp.key2 = line[pos + 1];
            pos += 3;
            if (pos >= line.size() || line[pos] != ':')
            {
                return false;
            }
            hasKey2 = true;
        }
        else if (line.compare(pos, 6, ":key3 ") == 0)
        {
            if (hasKey3)
            {
                return false;
            }
            pos += 6;
            if (pos >= line.size() || line[pos] != '"')
            {
                return false;
            }
            ++pos;
            const std::size_t endQuote = line.find('"', pos);
            if (endQuote == std::string::npos)
            {
                return false;
            }
            temp.key3 = line.substr(pos, endQuote - pos);
            pos = endQuote + 1;
            if (pos >= line.size() || line[pos] != ':')
            {
                return false;
            }
            hasKey3 = true;
        }
        else
        {
            return false;
        }
    }
    if (pos != line.size() - 2 || line[pos] != ':')
    {
        return false;
    }
    if (!hasKey1 || !hasKey2 || !hasKey3)
    {
        return false;
    }
    result = std::move(temp);
    return true;
}
std::istream& operator>>(std::istream& stream, DataStruct& data)
{
    std::string line;
    while (std::getline(stream, line))
    {
        DataStruct temp{};
        if (parseLine(line, temp))
        {
            data = std::move(temp);
            return stream;
        }
    }
    return stream;
}
std::string scientificToString(double value)
{
    std::ostringstream out;
    out << std::scientific << std::setprecision(1) << value;
    const std::string text = out.str();
    const std::size_t ePos = text.find('e');
    if (ePos == std::string::npos)
    {
        return text;
    }
    const std::string mantissa = text.substr(0, ePos);
    int exponent = 0;
    std::istringstream exponentStream(text.substr(ePos + 1));
    exponentStream >> exponent;
    std::ostringstream result;
    result << mantissa << 'e';
    if (exponent >= 0)
    {
        result << '+';
    }
    result << exponent;
    return result.str();
}
std::ostream& operator<<(std::ostream& stream, const DataStruct& data)
{
    return stream << "(:key1 " << scientificToString(data.key1) << ":key2 '" << data.key2 << "':key3 \"" << data.key3 << "\":)";
}
bool compareData(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 < rhs.key1)
    {
        return true;
    }
    if (rhs.key1 < lhs.key1)
    {
        return false;
    }
    if (lhs.key2 < rhs.key2)
    {
        return true;
    }
    if (rhs.key2 < lhs.key2)
    {
        return false;
    }
    return lhs.key3.size() < rhs.key3.size();
}
int main()
{
    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> inputBegin(std::cin);
    std::istream_iterator<DataStruct> inputEnd;
    std::copy(inputBegin, inputEnd, std::back_inserter(data));
    std::sort(data.begin(), data.end(), compareData);
    std::copy(data.cbegin(), data.cend(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
    return 0;
}