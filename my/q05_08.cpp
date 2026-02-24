#include "gtest/gtest.h"
#include "template.hpp"
#include <numeric>
#include <algorithm>
#include <ranges>
using std::vector;

constexpr double aqua(const int M, const vector<int> &a) {
  using std::accumulate;
  using std::next;
  using std::min;
  using std::views::iota;
  using std::views::transform;
  using std::ranges::to;
  using std::ranges::max_element;
  constexpr int INF = 1 << 29; // 十分大きな値

  const int N = a.size();

  assert(M >= 0 && M <= N);

  vector<vector<double>> dp(N + 1, vector<double>(M + 1, -INF));

  // 初期条件
  dp[0][0] = 0;

  // もらう方式
  for (int n = 1; n <= N; ++n) {
    for (int m = 1; m <= min(n, M); ++m) {
      // 一時変数をなくしたい
      const vector tmp = iota(0, n - m + 1)
                         | transform([=](const int i) {
                             return dp[n - i - 1][m - 1] + static_cast<double>(accumulate(next(a.end(), - N + n - i - 1), next(a.end(), - N + n), 0)) / (i + 1);
                           })
                         | to<vector>();  // 直接maxを取りたい
      dp[n][m] = *max_element(tmp);
    }
  }

  // debug
  print2d(dp);

  return dp[N][M];
}

TEST(TestSuite, Sample1) {
  const vector a {9, 1, 2, 3, 9};
  EXPECT_EQ(aqua(3, a), 20);
}

TEST(TestSuite, Sample2) {
  const vector a {14, 4, 9, 7};
  EXPECT_EQ(aqua(1, a), 8.5);
}

TEST(TestSuite, Sample3) {
  const vector a {11, 18, 9, 20, 4, 18, 12, 14};
  EXPECT_DOUBLE_EQ(aqua(3, a), 44.66666666666667);
}

TEST(TestSuite, M_Negative) {
  const vector a {9, 1, 2, 3, 9};
  EXPECT_DEATH(aqua(-1, a), "");
}
TEST(TestSuite, M_GreaterThan_N) {
  const vector a {9, 1, 2, 3, 9};
  EXPECT_DEATH(aqua(6, a), "");
}
