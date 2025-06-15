#include "gtest/gtest.h"
#include "union-find.hpp"
#include "graph.hpp"
#include <ranges>

// E: 辺集合 (連結かつ0以上の連番であること)
constexpr int bridges(const Pairs<int> &E) {
  const multimap M(E.begin(), E.end());
  const auto N = order_edge_set(M);

  const auto ev = std::views::iota(0u, E.size());
  int count = 0;

  for (const auto j : ev) {
    UnionFind uf(N);

    for (const auto i : ev) {
      if (i != j) {
        const auto [u, v] = E.at(i);
        uf.unite(u, v);
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
  const int gold;
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
    4,
  },
  {
    {
      {2, 2},
      {0, 1},
      {0, 2},
      {1, 2},
    },
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
    5,
  },
};

class TestSuite : public testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(bridges(GetParam().E), GetParam().gold);
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  TestSuite,
  testing::ValuesIn(PARAMS)
);
