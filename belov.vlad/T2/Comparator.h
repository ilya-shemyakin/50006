#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "DataStruct.h"

struct DataStructComparator {
    bool operator()(const DataStruct& lhs,
        const DataStruct& rhs) const {
        if (lhs.key1 != rhs.key1) {
            return lhs.key1 < rhs.key1;
        }

        const long double lhsValue =
            static_cast<long double>(lhs.key2.first) /
            static_cast<long double>(lhs.key2.second);

        const long double rhsValue =
            static_cast<long double>(rhs.key2.first) /
            static_cast<long double>(rhs.key2.second);

        if (lhsValue != rhsValue) {
            return lhsValue < rhsValue;
        }

        return lhs.key3.length() < rhs.key3.length();
    }
};

bool compareDataStruct(const DataStruct& lhs,
    const DataStruct& rhs) {
    return DataStructComparator{}(lhs, rhs);
}

#endif
