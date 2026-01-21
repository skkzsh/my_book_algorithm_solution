#include "gmock/gmock.h"
#include "union-find.hpp"
#include "graph.hpp"
#include <ranges>
#include <list>
using std::list;
using ::testing::ElementsAreArray;
using ::testing::Pair;

// E: 辺集合 (重み付き, 無向グラフ)
// 最小全域木の辺集合 (昇順) を返す
constexpr list<pair<int, int>> kruskal(const map<pair<int, int>, int> &E) {
  using std::views::keys;
  using std::views::transform;
  using std::ranges::to;

  const auto N = order_edge_set(E | keys | to<multimap>());

  // 重みで昇順sortするのに, multimapを使ってみる
  const auto sorted = E | transform([](const auto& p) {
            return pair{p.second, p.first};  // valueとkeyに反転
        })
        | to<multimap>();
  // debug
  // println("{}", sorted);

  list<pair<int, int>> results;
  UnionFind uf(N);

  for (const auto &[weight, edge] : sorted) {
    const auto &[u, v] = edge;
    if (!uf.is_same_set(u, v)) {
      uf.unite(u, v);
      results.push_back(edge);
      // debug
      // println("{}", edge);
    }
  }

  return results;
}

TEST(TestSuite, Ex) {
  const map<pair<int, int>, int> E {
      {{0, 3},  5},
      {{0, 5},  6},
      {{0, 7},  3},
      {{1, 4},  4},
      {{1, 6},  3},
      {{2, 4},  9},
      {{2, 5}, 10},
      {{2, 7},  5},
      {{3, 7},  6},
      {{4, 6},  2},
      {{6, 7},  7},
  };

  EXPECT_THAT(kruskal(E), ElementsAreArray({
    Pair(4, 6),
    Pair(0, 7),
    Pair(1, 6),
    Pair(0, 3),
    Pair(2, 7),
    Pair(0, 5),
    Pair(6, 7),
  }));
}
