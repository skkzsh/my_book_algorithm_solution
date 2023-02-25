#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include "template.hpp"
#include <numeric>

using std::vector;
using std::pair;

// n * p.second = p.first + d
// を満たすような最小の整数 d (>= 0) を返す
int count(const pair<int, int> p) {
    int n = 1;
    while (n * p.second < p.first) {
        ++n;
    }
    return n * p.second - p.first;
}

int min_push(Pairs<int> p) {
    vector<int> counts(p.size());

    for (int i = p.size() - 1; i >= 0; --i) {
        counts[i] = count(p[i]);
        // std::cout << "i: "  << i << ", count: " << counts[i] << std::endl;  // debug

        for (int j = i; j >= 0; --j) {
            p[j].first += counts[i];
        }
    }

    return std::accumulate(counts.begin(), counts.end(), 0);
}


TEST(TestSuite, a_greater_than_b) {
    EXPECT_EQ(count({9, 4}), 3);
}

TEST(TestSuite, a_less_than_b) {
    EXPECT_EQ(count({4, 9}), 5);
}

TEST(TestSuite, a_equal_to_multiple_of_b) {
    EXPECT_EQ(count({3, 1}), 0);
}


TEST_P(PairsIntSuite, Ex) {
    EXPECT_EQ(min_push(GetParam().p), GetParam().expected);
}

PairsIntParam params[] {
    {
        {
            {3, 5},
            {2, 7},
            {9, 4},
        },
        7,
    },
    {
        {
            {3, 1},
            {4, 1},
            {5, 9},
            {2, 6},
            {5, 3},
            {5, 8},
            {9, 7},
        },
        22
    },
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    PairsIntSuite,
    ::testing::ValuesIn(params)
);
