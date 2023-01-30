#include "gtest/gtest.h"
#include <algorithm>
#include "template.hpp"

int pair_max(pairs<int> r, pairs<int> b) {
    using std::ranges::sort;
    sort(r);
    sort(b);

    int i = 0;
    for (const auto &q : b) {
        if (r.at(i).first < q.first && r.at(i).second < q.second) {
            ++i;
        }
    }
    return i;
}


TEST(TestCase, Ex1) {
    const pairs<int> r {
        {2, 0},
        {3, 1},
        {1, 3},
    };
    const pairs<int> b {
        {4, 2},
        {0, 4},
        {5, 5},
    };

    EXPECT_EQ(pair_max(r, b), 2);
}

TEST(TestCase, Ex2) {
    const pairs<int> r {
        {0, 0},
        {1, 1},
        {5, 2},
    };
    const pairs<int> b {
        {2, 3},
        {3, 4},
        {4, 5},
    };

    EXPECT_EQ(pair_max(r, b), 2);
}

TEST(TestCase, Ex3) {
    const pairs<int> r {
        {2, 2},
        {3, 3},
    };
    const pairs<int> b {
        {0, 0},
        {1, 1},
    };

    EXPECT_EQ(pair_max(r, b), 0);
}

TEST(TestCase, Ex4) {
    const pairs<int> r {
        {0, 0},
        {7, 3},
        {2, 2},
        {4, 8},
        {1, 6},
    };
    const pairs<int> b {
        {8, 5},
        {6, 9},
        {5, 4},
        {9, 1},
        {3, 7},
    };

    EXPECT_EQ(pair_max(r, b), 5);
}

TEST(TestCase, Ex5) {
    const pairs<int> r {
        {0, 0},
        {1, 1},
        {5, 5},
        {6, 6},
        {7, 7},
    };
    const pairs<int> b {
        {2, 2},
        {3, 3},
        {4, 4},
        {8, 8},
        {9, 9},
    };

    EXPECT_EQ(pair_max(r, b), 4);
}
