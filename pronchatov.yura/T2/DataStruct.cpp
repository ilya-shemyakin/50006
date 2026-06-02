#include "DataStruct.h"
#include "IOFormat.h"

#include <iomanip>
#include <istream>
#include <ostream>
#include <string>

bool compareDataStruct(const DataStruct& left, const DataStruct& right)
{
    if (left.key1 != right.key1)
    {
        return left.key1 < right.key1;
    }

    if (left.key2 != right.key2)
    {
        return left.key2 < right.key2;
    }

    return left.key3.length() < right.key3.length();
}

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    DataStruct temp{}; // временный объект на случай если строка оказалась неправильной
    bool hasKey1 = false; // проверка что на входе есть все 3 поля
    bool hasKey2 = false;
    bool hasKey3 = false;

    in >> DelimeterIO{ '(' }; // сначала открывающая скобка
    if (!in)
    {
        return in;
    }

    while (!(hasKey1 && hasKey2 && hasKey3))
    {
        in >> DelimeterIO{ ':' }; // потом поиск разделителя
        if (!in)
        {
            return in;
        }

        std::string label;
        in >> label;
        if (!in)
        {
            return in;
        }

        if (label == "key1" && !hasKey1) // если key1 и раньше его не было
        {
            in >> DblSciIO{ temp.key1 }; // читаем значение
            if (!in)
            {
                return in;
            }
            hasKey1 = true; // ставим флаг
        }
        else if (label == "key2" && !hasKey2)
        {
            in >> UllBinIO{ temp.key2 };
            if (!in)
            {
                return in;
            }
            hasKey2 = true;
        }
        else if (label == "key3" && !hasKey3)
        {
            in >> StringIO{ temp.key3 };
            if (!in)
            {
                return in;
            }
            hasKey3 = true;
        }
        else
        {
            in.setstate(std::ios::failbit); // если поле неизвестное, то запись неправильная
            return in;
        }
    }

    in >> DelimeterIO{ ':' };
    if (!in)
    {
        return in;
    }

    in >> DelimeterIO{ ')' }; // чтение финальных символов
    if (!in)
    {
        return in;
    }

    dataStruct = temp;
    return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
        return out;
    }

    out << "(:";
    out << "key1 " << formatDblSci(dataStruct.key1) << ":";
    out << "key2 " << formatUllBin(dataStruct.key2) << ":";
    out << "key3 " << std::quoted(dataStruct.key3) << ":";
    out << ")";

    return out;
}
