#include "gtest/gtest.h"
#include <algorithm>
#include "template.hpp"
using std::vector;

unsigned int pair_max(Pairs<int> r, Pairs<int> b) {
    constexpr int INF = 1 << 29; // 十分大きな値

    using std::ranges::sort;
    sort(r);
    sort(b);

    vector<bool> used(r.size(), false);  // rが使用済かどうか
    unsigned int count = 0;

    for (size_t j = 0; j < b.size(); j++) {
        int max_second = - INF;
        std::optional<int> max_key;

        for (size_t i = 0; i < r.size(); i++) {
            if (!used.at(i) && r.at(i).first < b.at(j).first && r.at(i).second < b.at(j).second) {
                 if (max_second < r.at(i).second) {
                     max_second = r.at(i).second;
                     max_key = i;
                 }
            }
        }

        if (max_key.has_value()) {
            ++count;
            used.at(max_key.value()) = true;
        }
    }

    return count;
}


TEST(TestCase, Ex1) {
    const Pairs<int> r {
        {2, 0},
        {3, 1},
        {1, 3},
    };
    const Pairs<int> b {
        {4, 2},
        {0, 4},
        {5, 5},
    };

    EXPECT_EQ(pair_max(r, b), 2);
}

TEST(TestCase, Ex2) {
    const Pairs<int> r {
        {0, 0},
        {1, 1},
        {5, 2},
    };
    const Pairs<int> b {
        {2, 3},
        {3, 4},
        {4, 5},
    };

    EXPECT_EQ(pair_max(r, b), 2);
}

TEST(TestCase, Ex3) {
    const Pairs<int> r {
        {2, 2},
        {3, 3},
    };
    const Pairs<int> b {
        {0, 0},
        {1, 1},
    };

    EXPECT_EQ(pair_max(r, b), 0);
}

TEST(TestCase, Ex4) {
    const Pairs<int> r {
        {0, 0},
        {7, 3},
        {2, 2},
        {4, 8},
        {1, 6},
    };
    const Pairs<int> b {
        {8, 5},
        {6, 9},
        {5, 4},
        {9, 1},
        {3, 7},
    };

    EXPECT_EQ(pair_max(r, b), 5);
}

TEST(TestCase, Ex5) {
    const Pairs<int> r {
        {0, 0},
        {1, 1},
        {5, 5},
        {6, 6},
        {7, 7},
    };
    const Pairs<int> b {
        {2, 2},
        {3, 3},
        {4, 4},
        {8, 8},
        {9, 9},
    };

    EXPECT_EQ(pair_max(r, b), 4);
}
