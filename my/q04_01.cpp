#include "gtest/gtest.h"
using std::domain_error;

constexpr long long tribo(const int N) {
  if (N < 0) {
    throw domain_error("argument must not be negative");
  }

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
  EXPECT_THROW(tribo(-1), domain_error);
}
