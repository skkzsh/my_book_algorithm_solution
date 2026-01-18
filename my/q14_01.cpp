#include "gtest/gtest.h"
#include "graph.hpp"

// E: 辺集合
constexpr int longest_path(const multimap<int, int> &E) {
  const auto G = to_adjacency_list(E);

  // TODO: 実装
  return 2;
}

const struct TestParam {
  const multimap<int, int> E;
  const int gold;
} PARAMS[] {
  {
    {
      {1, 2},
      {1, 3},
      {3, 2},
      {2, 4},
      {3, 4},
    },
    3,
  },
  {
    {
      {2, 3},
      {4, 5},
      {5, 6},
    },
    2,
  },
  {
    {
      {5, 3},
      {2, 3},
      {2, 4},
      {5, 2},
      {5, 1},
      {1, 4},
      {4, 3},
      {1, 3},
    },
    3,
  },
};

class TestSuite : public testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  GTEST_SKIP() << "実装中のため";
  EXPECT_EQ(longest_path(GetParam().E), GetParam().gold);
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  TestSuite,
  testing::ValuesIn(PARAMS)
);
