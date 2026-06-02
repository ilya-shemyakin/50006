#include "DataStruct.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>


int main()
{
    std::vector<DataStruct> data;

    while (!std::cin.eof()) // цикл что бы поток в случае плохой строки очистился и строка пропустилась
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin), // оператор, который читает DataStruct из std::cin
            std::istream_iterator<DataStruct>(), // до куда мы идём, идём до конца ввода
            std::back_inserter(data) // куда копируем, в data. back_inserter нужен потому что data пустой и data.begin() указывает на data.end()
        );

        if (!std::cin.eof() && std::cin.fail()) // в случае неудачи пропускаем строку
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // пропускает остаток плохой строки до конца строки
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
