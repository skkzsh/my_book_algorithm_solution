#include "gtest/gtest.h"
#include "template.hpp"
using std::vector;

constexpr unsigned int INF = std::numeric_limits<unsigned int>::max();

bool partial_sum_exists_pull(const int W, const vector<int> a, const vector<unsigned int> m) {
    const int N = a.size();
    vector<vector<unsigned int>> dp(N + 1, vector<unsigned int>(W + 1, INF));

    // 初期条件
    dp[0][0] = 0;

    // もらう方式
    for (int n = 0; n < N; ++n) {
        for (int w = 0; w <= W; ++w) {
            // a[n]を選ぶ場合
            if (a[n] <= w && dp[n + 1][w - a[n]] < m[n]) {
                dp[n + 1][w] = dp[n + 1][w - a[n]] + 1;
            }
            // a[n]を選ばない場合
//            if (n > 0 && dp[n][w] <= m[n - 1]) { // TODO: 境界値 n = 0
            if (dp[n][w] < INF) {
                dp[n + 1][w] = 0;
            }
        }
    }

    // debug
    print2d(dp);

    return dp[N][W] <= m[N - 1];
}

bool partial_sum_exists_push(const int W, const vector<int> a, const vector<unsigned int> m) {
    const int N = a.size();
    vector<vector<unsigned int>> dp(N + 1, vector<unsigned int>(W + 1, INF));

    // 初期条件
    dp[0][0] = 0;

    // FIXME
    // 配る方式
    for (int n = 0; n <= N; ++n) {
        for (int w = 0; w <= W; ++w) {
            if (dp[n][w] <= m[n - 1]) {
                if (w + a[n - 1] <= W && dp[n][w] < m[n - 1]) { // TODO: 境界値 n = 0
//                if (w + a[n - 1] <= W) {
                    chmin(dp[n][w + a[n - 1]], dp[n][w] + 1);
                }
//                if (dp[n][w] < INF) {
                if (n < N) {
                    dp[n + 1][w] = 0;
                }
//                }
            }
        }
    }

    // debug
    print2d(dp);

    return dp[N][W] <= m[N - 1];
}


TEST(TestCase, TestFalse) {
    const vector<int> a {1, 2};
    const vector<unsigned int> m {1, 4};
    EXPECT_EQ(partial_sum_exists_pull(10, a, m), false);
    EXPECT_EQ(partial_sum_exists_push(10, a, m), false);
}

TEST(TestCase, TestTrue) {
    const vector<int> a {1, 2};
    const vector<unsigned int> m {2, 4};
    EXPECT_EQ(partial_sum_exists_pull(10, a, m), true);
    EXPECT_EQ(partial_sum_exists_push(10, a, m), true);
}
