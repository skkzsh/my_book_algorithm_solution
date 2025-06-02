#include "gtest/gtest.h"
#include <generator>

std::generator<long long> tribo_generator() {
  using std::tie;
  using std::tuple;

  for (long long a = 0, b = 0, c = 1 ;; tie(a, b, c) = tuple{b, c, a + b + c}) {
    co_yield a;
  }
}

TEST(TestSuite, Test20) {
  using std::views::take;

  long long result;

  for (const auto n : tribo_generator() | take(21)) {
    result = n;
  }

  EXPECT_EQ(result, 35890);
}
