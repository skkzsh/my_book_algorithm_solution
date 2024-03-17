#include "gtest/gtest.h"
using std::invalid_argument;

constexpr int count_simple(const int K, const int N) {
  int count = 0;
  for (int x = 0; x <= K; ++x) {
    for (int y = 0; y <= K; ++y) {
      if (const int z = N - x - y; z >= 0 && z <= K) {
        ++count;
      }
    }
  }
  return count;
}

constexpr int count_better(const int K, const int N) {
  if (K < 0 || N < 0) {
    throw invalid_argument("argument must not be negative");
  }

  if (3 * K < N) { // この場合, 条件を満たす組は存在しない
    return 0;
  }

  // K > nの場合, 0 <= x,y,z <= nの範囲のみ探索すれば十分
  const int boundary = std::min(K, N);

  int count = 0;
  for (int x = 0; x <= boundary; ++x) {
    for (int y = 0; y <= boundary; ++y) {
      if (const int z = N - x - y; z >= 0 && z <= K) {
        ++count;
      }
    }
  }
  return count;
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
