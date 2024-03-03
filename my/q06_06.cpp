#include "gtest/gtest.h"
#include <cmath> // Arch
#include <numbers> // Mac

using std::invalid_argument;
using std::tuple;
using std::pair;

template<class T> using Constants = tuple<T, T, T>;

constexpr double EPS = 1e-6; // 精度

constexpr double func(const double t, const Constants<int> &constants) {
  using std::sin;
  using std::numbers::pi;

  const auto [A, B, C] = constants;
  return A * t + B * sin(C * t * pi) - 100;
}

constexpr double bisection(const Constants<int> &constants, const pair<double, double> &interval) {

  auto [left, right] = interval;

  if (left >= right) {
    throw invalid_argument("left must be less than right");
  }

  // debug
  // std::cout << func(left, constants) << ' ' << func(right, constants) << std::endl;

  // func(left) < 0 かつ func(right) > 0 が必要条件
  if (func(left, constants) >= 0 || func(right, constants) <= 0) {
    throw invalid_argument("func(left) < 0 and func(right) > 0 required");
  }

  while (right - left > EPS) {
    if (const double t = (left + right) / 2; func(t, constants) >= 0) {
      right = t;
    } else {
      left = t;
    }
  }

  return right;
}

// 解は複数あるが, 返却値はそのうちの1つであり, 探索範囲によって変わることに注意

constexpr struct TestParam {
  const Constants<int> constants;
  const pair<double, double> interval;
  const double expected;
} PARAMS[] {
  { {1, 1, 1}, {0, 200}, 100 },
  { {53, 82, 49}, {1.58, 1.65}, 1.63372043395339 },
};

class TestSuite : public ::testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_NEAR(bisection(GetParam().constants, GetParam().interval), GetParam().expected, EPS);
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
