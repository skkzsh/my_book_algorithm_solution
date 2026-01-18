#include "gmock/gmock.h"
#include "graph.hpp"
#include <ranges>
using std::map;
using std::pair;
using ::testing::ElementsAreArray;

// E: 辺集合 (重み付き)
// s: 始点
constexpr vector<int> dijkstra(const map<pair<int, int>, int> &E, const int s) {
  using std::views::iota;
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
      {{0, 1},  3},
      {{0, 2},  5},
      {{1, 2},  4},
      {{1, 3}, 12},
      {{2, 3},  9},
      {{2, 4},  4},
      {{3, 5},  2},
      {{4, 3},  7},
      {{4, 5},  8},
  };

  EXPECT_THAT(dijkstra(E, 0), ElementsAreArray({0, 3, 5, 14, 9, 16}));
}
