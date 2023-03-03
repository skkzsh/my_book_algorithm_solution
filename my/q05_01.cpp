#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
using std::vector;

constexpr int happy_max(const vector<vector<int>> z) {
    using std::views::iota;
    using std::ranges::max_element;

    const int N = z.size();
    constexpr int M = 3;
    vector<vector<int>> dp(N + 1, vector<int>(M, 0));

    for (const int i : iota(0, N)) {
        for (const int j : iota(0, M)) {
            vector<int> tmp(M, -1); // TODO: views::(filter|transform)で直接作れないか
            for (const int k : iota(0, M)) {
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


TEST(TestSuite, Test0) {
    EXPECT_EQ(happy_max({}), 0);
}

TEST(TestSuite, Test1) {
    EXPECT_EQ(happy_max({{1, 3, 2}}), 3);
}

TEST(TestSuite, Test2) {
    const vector<vector<int>> z {
        {100, 10, 1},
        {110, 11, 2},
    };

    EXPECT_EQ(happy_max(z), 120);
}

TEST(TestSuite, Example1) {
    const vector<vector<int>> z {
        {10, 40, 70},
        {20, 50, 80},
        {30, 60, 90},
    };

    EXPECT_EQ(happy_max(z), 210);
}

TEST(TestSuite, Example3) {
    const vector<vector<int>> z {
        {6, 7, 8},
        {8, 8, 3},
        {2, 5, 2},
        {7, 8, 6},
        {4, 6, 8},
        {2, 3, 4},
        {7, 5, 1},
    };

    EXPECT_EQ(happy_max(z), 46);
}

