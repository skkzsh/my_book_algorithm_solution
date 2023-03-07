#include "gtest/gtest.h"
using std::vector;

bool partial_sum_exists_pull(const int W, const vector<int> a) { // TODO: constexpr (C++20)
  const int N = a.size();
  vector<vector<bool>> dp(N + 1, vector<bool>(W + 1, false));

  // 初期条件
  dp[0][0] = true;

  // もらう方式
  for (int n = 0; n < N; ++n) {
    for (int w = 0; w <= W; ++w) {
      dp[n + 1][w] = dp[n][w] || (a[n] <= w && dp[n + 1][w - a[n]]);
    }
  }

  return dp[N][W];
}

bool partial_sum_exists_push(const int W, const vector<int> a) { // TODO: constexpr (C++20)
  const int N = a.size();
  vector<vector<bool>> dp(N + 1, vector<bool>(W + 1, false));

  // 初期条件
  dp[0][0] = true;

  // 配る方式
  for (int n = 0; n <= N; ++n) {
    for (int w = 0; w <= W; ++w) {
      if (dp[n][w]) {
        if (n < N) {
          dp[n + 1][w] = true;
        }
        if (w + a[n] <= W) {
          dp[n][w + a[n]] = true;
        }
      }
    }
  }

  return dp[N][W];
}


TEST(TestSuite, TestTrue) {
  const vector<int> a {2};
  EXPECT_TRUE(partial_sum_exists_pull(10, a));
  EXPECT_TRUE(partial_sum_exists_push(10, a));
}

TEST(TestSuite, TestFalse) {
  const vector<int> a {3, 6, 8, 9, 11};
  EXPECT_FALSE(partial_sum_exists_pull(10, a));
  EXPECT_FALSE(partial_sum_exists_push(10, a));
}
