#include "gtest/gtest.h"

int happy_max(const int N, const std::vector<int> a, const std::vector<int> b, const std::vector<int> c) {
    if (N < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    std::vector<int> dp(N + 1, -1);
    dp[0] = 0;
    for(int i = 0; i < N; ++i) {
        // TODO: 2日連続で同じ行動はしない条件を追加する
        dp[i + 1] = dp[i] + std::max({a[i], b[i], c[i]});
    }

    return dp[N];
}


TEST(TestCase, Test0) {
    const std::vector<int> a = {};
    const std::vector<int> b = {};
    const std::vector<int> c = {};
    EXPECT_EQ(happy_max(0, a, b, c), 0);
}

TEST(TestCase, Test1) {
    const std::vector<int> a = {1};
    const std::vector<int> b = {3};
    const std::vector<int> c = {2};
    EXPECT_EQ(happy_max(1, a, b, c), 3);
}

TEST(TestCase, Test2) {
    const std::vector<int> a = {100, 110};
    const std::vector<int> b = {10, 11};
    const std::vector<int> c = {1, 2};
    EXPECT_EQ(happy_max(2, a, b, c), 120);
}

