#include "gtest/gtest.h"
#include <numeric>
#include "template.hpp"

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

int min_push(pairs<int> p) {
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


TEST(TestCase, a_greater_than_b) {
    EXPECT_EQ(count({9, 4}), 3);
}

TEST(TestCase, a_less_than_b) {
    EXPECT_EQ(count({4, 9}), 5);
}

TEST(TestCase, a_equal_to_multiple_of_b) {
    EXPECT_EQ(count({3, 1}), 0);
}


TEST(TestCase, Ex1) {
    const pairs<int> p {
        {3, 5},
        {2, 7},
        {9, 4},
    };

    EXPECT_EQ(min_push(p), 7);
}

TEST(TestCase, Ex2) {
    const pairs<int> p {
        {3, 1},
        {4, 1},
        {5, 9},
        {2, 6},
        {5, 3},
        {5, 8},
        {9, 7},
    };

    EXPECT_EQ(min_push(p), 22);
}
