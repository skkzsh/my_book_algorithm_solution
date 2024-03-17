#include "gtest/gtest.h"
#include "template.hpp"
#include <numeric>
#include <algorithm>

// TODO: 実装
constexpr int min_union_cost(const vector<int> &slimes) {
  using std::ranges::min_element;
  using std::accumulate;
  using std::next;

  constexpr int INF = 1 << 29; // 十分大きな値
  const int N = slimes.size();
  vector<vector<int>> dp(N + 1, vector<int>(N + 1, INF));

  // 初期条件
  for (int i = 0; i < N; ++i) {
    dp[i][i + 1] = 0;
  }

  // もらう方式
  for (int i = 0; i < N - 1; ++i) {
    for (int j = i + 2; j <= N; ++j) {
      vector<int> tmp(j - i, INF);
      for (int k = 0; k < j - i - 1; ++k) {
        tmp[k] = dp[i][i + 1 + k] + dp[i + 1 + k][j] + accumulate(next(slimes.begin(), i), next(slimes.begin(), j), 0);
      }
      dp[i][j] = *min_element(tmp);
    }
  }

  // debug
  print2d(dp);

  return dp[0][N];
}

TEST(TestSuite, Ex1) {
  EXPECT_EQ(min_union_cost({10, 20, 30, 40}), 190);
}

TEST(TestSuite, Ex2) {
  GTEST_SKIP() << "実装中のため";
  EXPECT_EQ(min_union_cost({10, 10, 10, 10}), 120);
}

TEST(TestSuite, Ex4) {
  GTEST_SKIP() << "実装中のため";
  EXPECT_EQ(min_union_cost({7, 6, 8, 6, 1, 1}), 68);
}
