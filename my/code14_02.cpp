#include "gmock/gmock.h"
#include "graph.hpp"
using ::testing::ElementsAreArray;

// E: 辺集合
constexpr vector<int> bellman_ford(const map<pair<int, int>, int> &E, const int s) {
  constexpr int INF = 1 << 29; // 十分大きな値

  const auto G = to_adjacency_list(E);
  // debug
  // print2d(G);

  vector<int> dists(G.size(), INF);
  dists.at(s) = 0;

  // TODO: 実装

  return dists;
}

TEST(TestSuite, Ex) {
  const map<pair<int, int>, int> E {
      {{0, 1},   3},
      {{0, 3}, 100},
      {{1, 2},  50},
      {{1, 3},  57},
      {{1, 4},  -4},
      {{2, 3}, -10},
      {{2, 4},  -5},
      {{2, 5}, 100},
      {{3, 1},  -5},
      {{4, 2},  57},
      {{4, 3},  25},
      {{4, 5},   8},
  };

  EXPECT_THAT(bellman_ford(E, 0), ElementsAreArray({0, 3, 53, 24, -1, 7}));
}

// TODO: negative cycle
