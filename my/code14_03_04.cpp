#include "gmock/gmock.h"
#include "graph.hpp"
#include <ranges>
#include <queue>
using ::testing::TestWithParam;
using ::testing::Combine;
using ::testing::ValuesIn;
using ::testing::Values;
using ::testing::ElementsAreArray;
using std::tuple;

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

  for (const auto _ : iota(0u, G.size())) {
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

    if (min_v.has_value()) {
      // 最小の頂点があれば, 使用済とする
      used.at(min_v.value()) = true;

      // 最小の頂点を始点とした各辺を緩和する
      for (const auto &[to, weight] : G.at(min_v.value())) {
        chmin(dists.at(to), dists.at(min_v.value()) + weight);
        // debug
        // println("{} -> {}: {}", min_v.value(), to, dists);
      }
    }

    // debug
    println("{}: {}, {}", min_v.value(), min_dist, dists);
    // println("{}", used);
  }

  return dists;
}

constexpr vector<int> dijkstra_heap(const map<pair<int, int>, int> &E, const int s) {
  using std::priority_queue;
  using std::greater;
  constexpr int INF = 1 << 29; // 十分大きな値

  const auto G = to_adjacency_list(E);

  vector<int> dists(G.size(), INF);
  // 昇順ヒープ {最短路長, 頂点}
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

  dists.at(s) = 0;
  pq.push({dists.at(s), s});

  while (!pq.empty()) {
    // 使用済でない頂点のうち, distが最小の頂点
    const auto [dist, v] = pq.top();
    pq.pop();

    if (dist <= dists.at(v)) { // ヒープに残ったゴミでなければ
      for (const auto &[to, weight] : G.at(v)) { // 頂点vを始点とした各辺を緩和する
        if (chminb(dists.at(to), dists.at(v) + weight)) {
          pq.push({dists.at(to), to}); // 更新があればヒープに追加
        }
      }
    }

    // debug
    println("{}: {}, {}, {}", v, dist, pq, dists);
  }

  return dists;
}


const struct TestParam {
  const map<pair<int, int>, int> E;
  const int s;
  const vector<int> gold;
} PARAMS[] {
  {
    {
      {{0, 1},  3},
      {{0, 2},  5},
      {{1, 2},  4},
      {{1, 3}, 12},
      {{2, 3},  9},
      {{2, 4},  4},
      {{3, 5},  2},
      {{4, 3},  7},
      {{4, 5},  8},
    },
    0,
    {0, 3, 5, 14, 9, 16},
  },
};

class TestSuite : public TestWithParam<tuple<TestParam, vector<int>(*)(const map<pair<int, int>, int> &, const int)>> {};

TEST_P(TestSuite, Ex) {
  const auto [p, algo] = GetParam();
  EXPECT_THAT(algo(p.E, p.s), ElementsAreArray(p.gold));
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  TestSuite,
  Combine(ValuesIn(PARAMS),
          Values(&dijkstra, &dijkstra_heap))
  // testing::PrintToStringParamName() // TODO
);
