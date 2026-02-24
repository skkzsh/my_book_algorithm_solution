#include "gtest/gtest.h"

constexpr long long tribo(const int N) {
  assert(N >= 0);

  // ベースケース
  switch (N) {
    case 0:
    case 1:  return 0;
    case 2:  return 1;
    default: return tribo(N - 1) + tribo(N - 2) + tribo(N - 3); // 再帰呼び出し
  }
}


TEST(TestSuite, Test30) {
  EXPECT_EQ(tribo(30), 15'902'591);
}

TEST(TestSuite, Negative) {
  EXPECT_DEATH(tribo(-1), "");
}
