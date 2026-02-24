#include "gtest/gtest.h"
#include <ranges>
using std::string_view;
using std::views::iota;

constexpr int sum_bit(const string_view S, const int bit) {
  const auto L = S.length();
  int sum = 0;
  int tmp = 0;

  for (const auto i : iota(0u, L - 1)) {
    const int num = S.at(i) - '0';
    assert(num >= 0 && num <= 9);

    tmp += num;

    if (bit & (1 << i)) {
      sum += tmp;
      tmp = 0;
    } else {
      tmp *= 10;
    }
  }

  sum += tmp;
  sum += S.at(L - 1) - '0';
  return sum;
}

constexpr int sum_combi(const string_view S) {
  const auto L = S.size();
  int sum_all = 0;

  for (const auto bit : iota(0, 1 << (L - 1))) {
    sum_all += sum_bit(S, bit);
  }

  return sum_all;
}


class SubTestSuite : public testing::TestWithParam<std::pair<int, int>> {};

TEST_P(SubTestSuite, Test) {
  const auto [bit, gold] = GetParam();
  EXPECT_EQ(sum_bit("125", bit), gold);
}

constexpr std::pair<int, int> PARAMS[] {
  {0b00, 125},
  {0b01, 26},
  {0b10, 17},
  {0b11, 8},
};

INSTANTIATE_TEST_SUITE_P(
  Inst,
  SubTestSuite,
  testing::ValuesIn(PARAMS),
  [](const testing::TestParamInfo<SubTestSuite::ParamType> &info) {
    return std::to_string(info.param.first);
  });

TEST(TestSuite, Test1) {
  EXPECT_EQ(sum_combi("125"), 176);
}

TEST(TestSuite, NotNumber) {
  EXPECT_DEATH(sum_combi("1?5"), "");
}
