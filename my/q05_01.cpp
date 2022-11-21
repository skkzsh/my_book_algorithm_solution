#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
using std::vector;

int happy_max(const int N, const vector<vector<int>> z) {
    using std::views::iota;
    using std::ranges::max_element;

    constexpr int M = 3;
    vector<vector<int>> dp(N + 1, vector<int>(M, 0));

    for (int i : iota(0, N)) {
        for (int j : iota(0, M)) {
            vector<int> tmp(M, -1); // TODO: views::(filter|transform)で直接作れないか
            for (int k : iota(0, M)) {
                if (k != j) {
                    tmp[k] = dp[i][k] + z[i][j];
                }
            }
            dp[i + 1][j] = *max_element(tmp);
        }
        // 2日連続で同じ行動してもいい場合
        // dp[i + 1] = dp[i] + std::max({a[i], b[i], c[i]});
    }

    return *max_element(dp[N]);
}


TEST(TestCase, Test0) {
    const vector<vector<int>> z {};

    EXPECT_EQ(happy_max(0, z), 0);
}

TEST(TestCase, Test1) {
    const vector<vector<int>> z {
        {1, 3, 2},
    };

    EXPECT_EQ(happy_max(1, z), 3);
}

TEST(TestCase, Test2) {
    const vector<vector<int>> z {
        {100, 10, 1},
        {110, 11, 2},
    };

    EXPECT_EQ(happy_max(2, z), 120);
}

TEST(TestCase, Example1) {
    const vector<vector<int>> z {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90},
    };

    EXPECT_EQ(happy_max(3, z), 210);
}

TEST(TestCase, Example3) {
    const vector<vector<int>> z {
        {6, 7, 8},
        {8, 8, 3},
        {2, 5, 2},
        {7, 8, 6},
        {4, 6, 8},
        {2, 3, 4},
        {7, 5, 1},
    };

    EXPECT_EQ(happy_max(7, z), 46);
}

