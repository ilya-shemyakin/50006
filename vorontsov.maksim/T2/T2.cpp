#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "DataStruct.h"
#include "Comparator.h"

int main() {
    std::vector<DataStruct> data{};
    std::string line{};

    while (std::getline(std::cin, line)) {
        std::istringstream lineStream(line);
        DataStruct item{};

        if (lineStream >> item) {
            data.push_back(item);
        }
    }

    std::sort(data.begin(), data.end(), compareDataStruct);

    std::copy(
        data.begin(),
        data.end(),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
