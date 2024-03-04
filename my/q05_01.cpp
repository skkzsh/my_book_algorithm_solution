#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include <algorithm>
#include <ranges>
using std::vector;

constexpr int happy_max(const vector<vector<int>> &z) {
  using std::views::iota;
  using std::ranges::max_element;

  const size_t N = z.size();
  constexpr size_t M = 3;
  vector<vector<int>> dp(N + 1, vector<int>(M));

  for (const auto i : iota(0u, N)) {
    for (const auto j : iota(0u, M)) {
      vector<int> tmp(M, -1); // TODO: views::(filter|transform), ranges::to (C++23)
      for (const auto k : iota(0u, M)) {
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


class TestSuite : public ::testing::TestWithParam<SingleTestParam<vector<vector<int>>>> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(happy_max(GetParam().x), GetParam().gold);
}

const SingleTestParam<vector<vector<int>>> PARAMS[] {
  { {}, 0 },
  { {{1, 3, 2}}, 3 },
  {
    {
      {100, 10, 1},
      {110, 11, 2},
    },
    120,
  },
  {
    {
      {10, 40, 70},
      {20, 50, 80},
      {30, 60, 90},
    },
    210,
  },
  {
    {
      {6, 7, 8},
      {8, 8, 3},
      {2, 5, 2},
      {7, 8, 6},
      {4, 6, 8},
      {2, 3, 4},
      {7, 5, 1},
    },
    46,
  },
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
