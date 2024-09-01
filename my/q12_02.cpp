#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
#include <expected>
// using std::invalid_argument;
using std::expected;
using std::unexpected;
using std::string;

constexpr expected<int, string> min_cost(Pairs<int> shops, const int M) { // {cost, count}
  std::ranges::sort(shops);

  int cost = 0;
  int count = 0;

  for (const auto &[A, B] : shops) {
    for (int i = 0; i < B; ++i) {
      cost += A;
      ++count;
      if (count == M) {
        return cost;
      }
    }
  }

  // throw invalid_argument("Cannot");
  return unexpected("Cannot");
}


const struct TestParam {
  const Pairs<int> shops;
  const int M;
  const expected<int, string> gold;
} PARAMS[] {
  {
    {
      {4, 1},
      {2, 4},
    },
    5,
    12,
  },
  {
    {
      {6, 18},
      {2, 5},
      {3, 10},
      {7, 9},
    },
    30,
    130,
  },
  {
    {
      {4, 1},
      {2, 4},
    },
    6,
    unexpected("Cannot"),
  },
};

class TestSuite : public testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(min_cost(GetParam().shops, GetParam().M), GetParam().gold);
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  TestSuite,
  testing::ValuesIn(PARAMS)
);

// TEST(InvalidTestSuite, Cannot) {
//   const Pairs<int> shops {
//     {4, 1},
//     {2, 4},
//   };
//   EXPECT_THROW(min_cost(shops, 6), invalid_argument);
// }
