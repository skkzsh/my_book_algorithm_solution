#include "gtest/gtest.h"
#include <algorithm>
using std::vector;

// O(N^2 log N)
int product_th(const vector<int> a, const vector<int> b, const int K) {
    vector<int> p; // (a.size() * b.size())
    for (const int i : a) {
        for (const int j : b) {
            p.push_back(i * j);
        }
    }
    std::ranges::sort(p);
    return p[K - 1];
}

TEST(TestCase, Ex1) {
    EXPECT_EQ(product_th({2, 3}, {3, 5}, 3), 10);
}

TEST(TestCase, Ex2) {
    EXPECT_EQ(product_th({1, 2, 1}, {2, 1, 2}, 7), 2);
}
