#include "gmock/gmock.h"
#include "graph.hpp"
#include <queue>
#include <ranges>
using ::testing::ElementsAreArray;
using std::vector;

// G: 隣接リスト (無向グラフ)
// 連結かつ0以上の連番であること
// 隣接リストが無向グラフとして整合していること (2->5があるなら5->2があること)
vector<int> BFS(const vector<vector<int>> &G, const int s) {
  order_adjacency_list(G);

  using std::optional;
  using std::ranges::transform;

  vector<optional<int>> dists(G.size());
  std::queue<int> todo;

  dists.at(s) = 0;
  todo.push(s);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();

    for (const auto x : G.at(v)) {
      if (!dists.at(x).has_value()) {
        dists.at(x) = dists.at(v).value() + 1;
        todo.push(x);
      }
    }
  }

  // optionalはがし
  vector<int> results(G.size());
  transform(dists, results.begin(),
            [](const auto x) { return x.value(); }  // TODO: optional<auto> or auto
            );

  // TODO: C++23
  // using std::views::transform;
  // using std::ranges::to;

  return results;
}

TEST(TestSuite, Ex) {
  const vector<vector<int>> G {
    {1, 2, 4},
    {0, 3, 4, 8},
    {0, 5},
    {1, 7, 8},
    {0, 1, 8},
    {2, 6, 8},
    {5, 7},
    {3, 6},
    {1, 3, 4, 5},
  };

  EXPECT_THAT(BFS(G, 0), ElementsAreArray({0, 1, 1, 2, 1, 2, 3, 3, 2}));
}
