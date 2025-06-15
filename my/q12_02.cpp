#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
// #include <expected>
// using std::invalid_argument;
// using std::expected;
// using std::unexpected;
// using std::string;
using std::optional;
using std::nullopt;

constexpr optional<int> min_cost(Pairs<int> shops, const int M) { // {cost, count}
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

  return nullopt;
  // return unexpected("Cannot");
  // throw invalid_argument("Cannot");
}


const struct TestParam {
  const Pairs<int> shops;
  const int M;
  const optional<int> gold;
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
    nullopt,
    // unexpected("Cannot"),
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
