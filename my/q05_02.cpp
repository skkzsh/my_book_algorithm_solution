#include "gtest/gtest.h"
using std::vector;

bool partial_sum_exists_pull(const int W, const vector<int> a) {
    const int N = a.size();
    vector<vector<bool>> dp(N + 1, vector<bool>(W + 1, false));

    // 初期条件
    dp[0][0] = true;
    // for (int w = 1; w <= W; ++w) {
    //     dp[0][w] = false;
    // }

    // a[n]を選ぶ場合
    // n - 1 のときw - a[n]でtrueならtrue

    // もらう方式
    for (int n = 0; n < N; ++n) {
        for (int w = 0; w <= W; ++w) {
            if(dp[n][w] || (a[n] <= w && dp[n][w - a[n]])) {
                dp[n + 1][w] = true;
            }
        }
    }

    return dp[N][W];
}

bool partial_sum_exists_push(const int W, const vector<int> a) {
    const int N = a.size();
    vector<vector<bool>> dp(N + 1, vector<bool>(W + 1, false));

    // 初期条件
    dp[0][0] = true;
    // for (int w = 1; w <= W; ++w) {
    //     dp[0][w] = false;
    // }

    // 配る方式
    for (int n = 0; n < N; ++n) {
        for (int w = 0; w <= W; ++w) {
            if(dp[n][w]) {
                dp[n + 1][w] = true;
                if(w + a[n] <= W) {
                    dp[n + 1][w + a[n]] = true;
                }
            }
        }
    }

    return dp[N][W];
}


TEST(TestCase, TestTrue) {
    const vector<int> a {1, 2, 4, 5, 11};
    EXPECT_EQ(partial_sum_exists_pull(10, a), true);
    EXPECT_EQ(partial_sum_exists_push(10, a), true);
}

TEST(TestCase, TestFalse) {
    const vector<int> a {1, 5, 8, 11};
    EXPECT_EQ(partial_sum_exists_pull(10, a), false);
    EXPECT_EQ(partial_sum_exists_push(10, a), false);
}
