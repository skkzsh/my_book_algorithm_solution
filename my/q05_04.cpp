#include "gtest/gtest.h"
#include "template.hpp"
using std::vector;

constexpr int INF = 1 << 29; // 十分大きな値

constexpr bool partial_sum_exists_pull(const int W, const int K, const vector<int> &a) {
  assert(K >= 0);

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

constexpr bool partial_sum_exists_push(const int W, const int K, const vector<int> &a) {
  assert(K >= 0);

  const int N = a.size();
  vector<vector<int>> dp(N + 1, vector<int>(W + 1, INF));

  // 初期条件
  dp[0][0] = 0;

  // 配る方式
  for (int n = 0; n < N; ++n) {
    for (int w = 0; w <= W; ++w) {
      chmin(dp[n + 1][w], dp[n][w]);
      if (w + a[n] <= W) {
        chmin(dp[n + 1][w + a[n]], dp[n][w] + 1);
      }
    }
  }

  return dp[N][W] <= K;
}

TEST(TestSuite, TestFalse) {
  const vector a {1, 2, 4, 5, 11};
  EXPECT_FALSE(partial_sum_exists_pull(10, 2, a));
  EXPECT_FALSE(partial_sum_exists_push(10, 2, a));
}

TEST(TestSuite, TestTrue) {
  const vector a {1, 2, 4, 5, 11};
  EXPECT_TRUE(partial_sum_exists_pull(10, 3, a));
  EXPECT_TRUE(partial_sum_exists_push(10, 3, a));
}

TEST(TestSuite, K_Negative) {
  const vector a {1, 2, 4, 5, 11};
  EXPECT_DEATH(partial_sum_exists_pull(10, -1, a), "");
  EXPECT_DEATH(partial_sum_exists_push(10, -1, a), "");
}
