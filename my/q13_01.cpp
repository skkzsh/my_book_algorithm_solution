#include "gtest/gtest.h"
#include "graph.hpp"
#include <ranges>

int count_connected(const multimap<int, int> &E, auto search) {
  using std::views::iota;

  const auto G = to_adjacency_list(E);

  vector<bool> seen(G.size());
  int count = 0;

  for (const auto v : iota(0, static_cast<int>(G.size()))) {
    if (!seen.at(v)) {
      search(G, v, seen);
      count++;
    }
  }

  return count;
}


const struct TestParam {
  const multimap<int, int> E;
  const int gold;
} PARAMS[] {
  {
    {
      {0, 1},
      {0, 2},
      {0, 4},
      {1, 3},
      {1, 4},
      {1, 8},
      {2, 5},
      {3, 7},
      {3, 8},
      {4, 8},
      {5, 6},
      {5, 8},
      {6, 7},
    },
    1,
  },
  {
    {
      {0, 1},
      // {0, 2}, // (2, 5) を孤立させる
      {0, 4},
      {1, 3},
      {1, 4},
      {1, 8},
      {2, 5},
      // {3, 7}, // (6, 7) を孤立させる
      {3, 8},
      {4, 8},
      // {5, 6}, // (6, 7) を孤立させる
      // {5, 8}, // (2, 5) を孤立させる
      {6, 7},
    },
    3,
  }
};

class TestSuite : public ::testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(count_connected(GetParam().E, recursive_search), GetParam().gold);
  EXPECT_EQ(count_connected(GetParam().E, bfs), GetParam().gold);
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
