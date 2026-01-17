#include "gmock/gmock.h"
#include "graph.hpp"
using ::testing::ElementsAreArray;

// E: 辺集合
constexpr vector<int> bellman_ford(const map<pair<int, int>, int> &E, const int s) {
  using std::views::iota;
  constexpr int INF = 1 << 29; // 十分大きな値

  const auto G = to_adjacency_list(E);
  // debug
  // print2d(G);

  vector<int> dists(G.size(), INF);
  dists.at(s) = 0;

  for (const auto i : iota(0u, G.size())) { // 始点sから到達可能な負閉路を持たないなら, 高々頂点数-1回の反復で収束する
    for (const auto u : iota(0u, G.size())) {
      if (dists.at(u) != INF) {
        for (const auto &[v, l] : G.at(u)) {
          chmin(dists.at(v), dists.at(u) + l);
        }
      }
    }
  }

  return dists;
}

TEST(TestSuite, Ex) {
  const map<pair<int, int>, int> E {
      // 非常に効率の悪い順序で定義
      // ...だけどmapは順不同だし, 内部で隣接リスト (vector) 化されるので意味はない
      {{2, 3}, -10},
      {{2, 4},  -5},
      {{2, 5}, 100},
      {{4, 2},  57},
      {{4, 3},  25},
      {{4, 5},   8},
      {{3, 1},  -5},
      {{1, 2},  50},
      {{1, 3},  57},
      {{1, 4},  -4},
      {{0, 1},   3},
      {{0, 3}, 100},
  };

  // debug
  // for (const auto &x : E) {
  //   println("{} ", x);
  // }

  EXPECT_THAT(bellman_ford(E, 0), ElementsAreArray({0, 3, 53, 24, -1, 7}));
}

// TODO: negative cycle
