#include "gtest/gtest.h"
#include "template.hpp"
using std::vector;

// 十分大きな値
const int INF = 1 << 29;

bool partial_sum_exists_pull(const int W, const int K, const vector<int> a) {
     if (K < 0) {
         throw std::invalid_argument("K must be not negative");
     }

    const int N = a.size();
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, INF));

    // 初期条件
    dp[0][0] = 0;

    // もらう方式
    for (int n = 0; n < N; ++n) {
        for (int w = 0; w <= W; ++w) {
            // a[n]を選ばない場合
            dp[n + 1][w] = dp[n][w];
            // a[n]を選ぶ場合
            if (a[n] <= w) {
                chmin(dp[n + 1][w], dp[n][w - a[n]] + 1);
            }
        }
    }

    return dp[N][W] <= K;
}

bool partial_sum_exists_push(const int W, const int K, const vector<int> a) {
     if (K < 0) {
         throw std::invalid_argument("K must be not negative");
     }

    const int N = a.size();
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, INF));

    // 初期条件
    dp[0][0] = 0;

    // 配る方式
    for (int n = 0; n < N; ++n) {
        for (int w = 0; w <= W; ++w) {
            chmin(dp[n + 1][w], dp[n][w]);
            if(w + a[n] <= W) {
                chmin(dp[n + 1][w + a[n]], dp[n][w] + 1);
            }
        }
    }

    return dp[N][W] <= K;
}

TEST(TestCase, TestFalse) {
    const vector<int> a = {1, 2, 4, 5, 11};
    EXPECT_EQ(partial_sum_exists_pull(10, 2, a), false);
    EXPECT_EQ(partial_sum_exists_push(10, 2, a), false);
}

TEST(TestCase, TestTrue) {
    const vector<int> a = {1, 2, 4, 5, 11};
    EXPECT_EQ(partial_sum_exists_pull(10, 3, a), true);
    EXPECT_EQ(partial_sum_exists_push(10, 3, a), true);
}

TEST(TestCase, K_Negative) {
    const vector<int> a = {1, 2, 4, 5, 11};
    EXPECT_THROW(partial_sum_exists_pull(10, -1, a), std::invalid_argument);
    EXPECT_THROW(partial_sum_exists_push(10, -1, a), std::invalid_argument);
}
