#include "gtest/gtest.h"
#include "graph.hpp"
#include <expected>
using std::expected;
using std::unexpected;
using ::testing::TestWithParam;
using ::testing::ValuesIn;

// E: 辺集合 (重み付き)
// s: 始点
// いくらでも大きくできる場合は, unexpectedを返す
constexpr expected<int, bool> longest_path(const map<pair<int, int>, int> &E, const int s) {
  // TODO: 実装
  return E.size() + s;
}


const struct TestParam {
  const map<pair<int, int>, int> E;
  const int s;
  const expected<int, bool> gold;
} PARAMS[] {
  {
    {
      {{1, 2}, 4},
      {{2, 3}, 3},
      {{1, 3}, 5},
    },
    0,
    7,
  },
  {
    {
      {{1, 2}, 1},
      {{2, 1}, 1},
    },
    0,
    unexpected(true),
  },
  {
    {
      {{1, 2}, -1'000'000'000},
      {{2, 3}, -1'000'000'000},
      {{3, 4}, -1'000'000'000},
      {{4, 5}, -1'000'000'000},
      {{5, 6}, -1'000'000'000},
    },
    0,
    -5'000'000'000,
  },
};

class TestSuite : public TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  GTEST_SKIP() << "実装中のため";
  EXPECT_EQ(longest_path(GetParam().E, GetParam().s), GetParam().gold);
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  TestSuite,
  ValuesIn(PARAMS)
  // testing::PrintToStringParamName() // TODO
);
