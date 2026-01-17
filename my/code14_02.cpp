#include "gmock/gmock.h"
#include "graph.hpp"
#include <ranges>
#include <expected>
using std::expected;
using std::unexpected;
using std::map;
using std::pair;
using ::testing::ElementsAreArray;

// E: 辺集合 (重み付き)
// s: 始点
// 始点sから到達可能な負閉路を持つ場合, unexpectedを返す
constexpr expected<vector<int>, bool> bellman_ford(const map<pair<int, int>, int> &E, const int s) {
  using std::views::keys;
  using std::ranges::to;
  using std::views::iota;
  constexpr int INF = 1 << 29; // 十分大きな値

  const auto N = order_edge_set(E | keys | to<multimap>());

  vector dists(N, INF);
  dists.at(s) = 0;

  for (const auto i : iota(0u, N)) { // 始点sから到達可能な負閉路を持たないなら, 高々頂点数-1回の反復で収束する
    bool updated = false; // 更新があったかどうか

    for (const auto &[edge, weight] : E) {
      const auto &[from, to] = edge;

      // 始点が到達可能な頂点であれば, 緩和する
      if (dists.at(from) != INF) {
          updated = chminb(dists.at(to), dists.at(from) + weight);
      }
    }

    // 更新がなければ (収束したら) 反復を終わっていい
    if (!updated) {
      break;
    }

    // 頂点数回目の反復でも更新があった <=> 始点sから到達可能な負閉路を持つ
    if (i == N - 1 && updated) {
      return unexpected(true);
    }
  }

  return dists;
}

TEST(TestSuite, Ex) {
  const map<pair<int, int>, int> E {
      // 非常に効率の悪い順序で定義
      // ...だけどmapなので意味はない
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

  EXPECT_THAT(bellman_ford(E, 0).value(), ElementsAreArray({0, 3, 53, 24, -1, 7}));
}

TEST(TestSuite, HasNegativeCycle) {
  const map<pair<int, int>, int> E {
      {{2, 3}, -10},
      {{2, 4},  -5},
      {{2, 5}, 100},
      {{4, 2},  57},
      {{4, 3},  25},
      {{4, 5},   8},
      {{3, 1},  -5},
      {{1, 2}, -50}, // 負閉路にする
      {{1, 3},  57},
      {{1, 4},  -4},
      {{0, 1},   3},
      {{0, 3}, 100},
  };

  EXPECT_EQ(bellman_ford(E, 0), unexpected(true));
}
