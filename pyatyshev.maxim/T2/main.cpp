#include "DataStruct.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <limits>

int main()
{
    std::vector<DataStruct> data;


    while (true) {
        auto begin = std::istream_iterator<DataStruct>(std::cin);
        auto end = std::istream_iterator<DataStruct>();

        std::copy(begin, end, std::back_inserter(data));

        if (std::cin.eof()) {
            break;
        }

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }


    std::sort(data.begin(), data.end(),
              [](const DataStruct& lhs, const DataStruct& rhs) {
                  if (std::abs(lhs.key1 - rhs.key1) > 1e-9) {
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


