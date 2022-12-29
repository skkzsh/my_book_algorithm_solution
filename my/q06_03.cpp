#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
#include <cmath>

int darts_simple(const std::vector<int> a, const int M) {
    int max = -1;

    for (const int p : a) {
        for (const int q : a) {
            for (const int r : a) {
                for (const int s : a) {
                    const int tmp = p + q + r + s;
                    if (tmp < M) {
                        chmax(max, tmp);
                    }
                }
            }
        }
    }

    return max;
}

int darts_binary(const std::vector<int> a, const int M) {
    using namespace std::ranges;
    constexpr int L = 4;
    std::vector<int> aa(std::pow(a.size(), L));

    for (const int p : a) {
        for (const int q : a) {
            for (const int r : a) {
                for (const int s : a) {
                    aa.push_back(p + q + r + s);
                }
            }
        }
    }

    sort(aa);
    return *std::prev(lower_bound(aa, M));
}

TEST(TestCase, Ex1) {
    EXPECT_EQ(darts_simple({3, 14, 15, 9}, 50), 48);
    EXPECT_EQ(darts_binary({3, 14, 15, 9}, 50), 48);
}
