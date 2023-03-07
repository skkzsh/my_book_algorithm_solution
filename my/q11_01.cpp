#include "gtest/gtest.h"
#include "union-find.hpp"
#include "template.hpp"
#include <ranges>

// E: 辺集合 (連結かつ0以上の連番であること)
// N: 頂点数 (Gと整合が取れていること)
constexpr int bridges(const Pairs<int> E, const int N) {
  auto edge_view = std::views::iota(0, (int) E.size());
  // const int N = ;  // TODO
  int count = 0;

  for (const int j : edge_view) {
    UnionFind uf(N);

    for (const int i : edge_view) {
      if (i != j) {
        uf.unite(E.at(i).first, E.at(i).second);
      }
    }

    if (uf.count_set() > 1) {
      ++count;
    }
  }

  return count;
}


const struct TestParam {
  const Pairs<int> E;
  const int N;
  const int expected;
} PARAMS[] {
  {
    {
      {0, 2},
      {1, 6},
      {2, 3},
      {3, 4},
      {3, 5},
      {4, 5},
      {5, 6},
    },
    7,
    4,
  },
  {
    {
      {2, 2},
      {0, 1},
      {0, 2},
      {1, 2},
    },
    3,
    0,
  },
  {
    {
      {0, 1},
      {1, 2},
      {2, 3},
      {3, 4},
      {4, 5},
    },
    6,
    5,
  },
};

class TestSuite : public ::testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(bridges(GetParam().E, GetParam().N), GetParam().expected);
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
