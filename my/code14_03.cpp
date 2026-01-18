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
  using std::optional;
  constexpr int INF = 1 << 29; // 十分大きな値

  const auto G = to_adjacency_list(E);
  // debug
  // print2d(G);

  vector<bool> used(G.size());
  vector<int> dists(G.size(), INF);
  dists.at(s) = 0;

  for (const auto i : iota(0u, G.size())) {
    // 使用済でない頂点のうち, distsが最小の頂点を探す
    // min_elementは使えない?
    int min_dist = INF;
    optional<int> min_v;

    for (const auto v : iota(0u, G.size())) {
      if (!used.at(v) && dists.at(v) < min_dist) {
        min_dist = dists.at(v);
        min_v = v;
      }
    }
    // debug
    // std::println("{}: {}", min_v.value(), min_dist);

    if (min_v.has_value()) {
      // 最小の頂点があれば, 使用済とする
      used.at(min_v.value()) = true;

      // 最小の頂点を始点とした各辺を緩和する
      for (const auto &[to, weight] : G.at(min_v.value())) {
        chmin(dists.at(to), dists.at(min_v.value()) + weight);
      }
    }
  }

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
