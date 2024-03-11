#include "gmock/gmock.h"
#include "graph.hpp"
#include <queue>
#include <ranges>
using ::testing::ElementsAreArray;
using std::vector;

// E: 辺集合
vector<int> BFS(const Pairs<int> &E, const int s) {
  const vector<vector<int>> G = to_adjacency_list(E);

  using std::optional;
  using std::ranges::transform;

  vector<optional<int>> dists(G.size());
  std::queue<int> todo;

  dists.at(s) = 0;
  todo.push(s);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();

    for (const auto n : G.at(v)) {
      if (!dists.at(n).has_value()) {
        dists.at(n) = dists.at(v).value() + 1;
        todo.push(n);
      }
    }
  }

  // optionalはがし
  vector<int> results(G.size());
  transform(dists, results.begin(),
            [](const auto o) { return o.value(); }  // TODO: optional<auto> or auto
            );

  // TODO: C++23
  // using std::views::transform;
  // using std::ranges::to;

  return results;
}

TEST(TestSuite, Ex) {
  const Pairs<int> E {
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
  };

  EXPECT_THAT(BFS(E, 0), ElementsAreArray({0, 1, 1, 2, 1, 2, 3, 3, 2}));
}
