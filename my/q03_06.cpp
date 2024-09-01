#include "gtest/gtest.h"
#include <ranges>
#include <algorithm>
using std::invalid_argument;
using std::views::iota;
using std::views::cartesian_product;
using std::ranges::count_if;

consteval int count_simple(const int K, const int N) {
  const auto seq = iota(0, K + 1);

  return count_if(
    cartesian_product(seq, seq),
    [K, N](const auto &t) { // TODO: 構造化束縛を簡潔に or なくしたい
      const auto &[x, y] = t;
      const int z = N - x - y;
      return 0 <= z && z <= K;
    });
}

constexpr int count_better(const int K, const int N) {
  if (K < 0 || N < 0) {
    throw invalid_argument("argument must not be negative");
  }

  if (3 * K < N) { // この場合, 条件を満たす組は存在しない
    return 0;
  }

  // K > nの場合, 0 <= x,y,z <= nの範囲のみ探索すれば十分
  const auto seq = iota(0, std::min(K, N) + 1);

  return count_if(
    cartesian_product(seq, seq),
    [K, N](const auto &t) { // TODO: 構造化束縛を簡潔に or なくしたい
      const auto &[x, y] = t;
      const int z = N - x - y;
      return 0 <= z && z <= K;
    });
}

// TODO: combine

TEST(TestSuite, SolutionNotExists) {
  EXPECT_EQ(count_simple(3, 10), 0);
  EXPECT_EQ(count_better(3, 10), 0);
}

TEST(TestSuite, k_equal_to_n) {
  EXPECT_EQ(count_simple(3, 3), 10);
  EXPECT_EQ(count_better(3, 3), 10);
}

TEST(TestSuite, k_greater_than_n) {
  EXPECT_EQ(count_simple(10, 3), 10);
  EXPECT_EQ(count_better(10, 3), 10);
}

TEST(TestSuite, k_negative) {
  EXPECT_THROW(count_better(-1, 3), invalid_argument);
}

TEST(TestSuite, n_negative) {
  EXPECT_THROW(count_better(3, -1), invalid_argument);
}
