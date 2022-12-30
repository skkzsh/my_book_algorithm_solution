#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
using std::vector;

// O(N^4)
int darts_simple(const vector<int> a, const int M) {
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

// O(N^2 log N)
int darts_binary(const vector<int> a, const int M) {
    using namespace std::ranges;

    if (4 * *min_element(a) >= M) {
        throw std::invalid_argument("Solution does not exist");
    }

    vector<int> aa(a.size() * a.size());
    for (const int i : a) {
        for (const int j : a) {
            aa.push_back(i + j);
        }
    }
    sort(aa);

    vector<int> tmp(aa.size());
    for (const int k : aa) {
        tmp.push_back(k + *std::prev(lower_bound(aa, M - k)));
    }

    return *max_element(tmp);
}

TEST(TestCase, Ex1) {
    EXPECT_EQ(darts_simple({3, 14, 15, 9}, 50), 48);
    EXPECT_EQ(darts_binary({3, 14, 15, 9}, 50), 48);
}

TEST(TestCase, InvalidArgumentTest) {
    EXPECT_EQ(darts_simple({1}, 4), -1);
    EXPECT_THROW(darts_binary({1}, 4), std::invalid_argument);
}
