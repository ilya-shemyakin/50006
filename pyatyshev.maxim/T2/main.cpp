#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<DataStruct> data;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(data));

    std::sort(data.begin(), data.end(),
        [](const DataStruct& lhs, const DataStruct& rhs) {
            if (lhs.key1 != rhs.key1) {
                return lhs.key1 < rhs.key1;
            }
            if (lhs.key2 != rhs.key2) {
                return lhs.key2 < rhs.key2;
            }
            return lhs.key3.length() < rhs.key3.length();
        });

    std::copy(data.begin(), data.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}



