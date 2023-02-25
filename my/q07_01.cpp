#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include <algorithm>
using std::vector;

// 前提
// a[0] <= a[i]
// b[0] <= b[j]
// 定義
// a[i] < b[0]
// a[0] < b[j]
// =>
// a[0] <= a[i] < b[0] <= b[j]
// =>
// a[0] < b[0]
// a[i] < b[j]
// => 交換可能

int max_pairing(vector<int> a, vector<int> b) {
    using std::sort; // TODO: using ranges
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0;
    for (const int m : b) {
        if (a.at(i) < m) {
            ++i;
        }
    }
    return i;
}


TEST_P(PairVectorIntSuite, Ex) {
    EXPECT_EQ(max_pairing(GetParam().a, GetParam().b), GetParam().expected);
}

const PairVectorIntParam params[] {
    {
        {2, 3, 1},
        {4, 0, 5},
        2,
    },
    {
        {0, 1, 5},
        {2, 3, 4},
        2,
    },
    {
        {2, 3},
        {0, 1},
        0,
    },
    {
        {0, 7, 2, 4, 1},
        {8, 6, 5, 9, 3},
        5,
    },
    {
        {0, 1, 5, 6, 7},
        {2, 3, 4, 8, 9},
        4,
    },
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    PairVectorIntSuite,
    ::testing::ValuesIn(params)
);
