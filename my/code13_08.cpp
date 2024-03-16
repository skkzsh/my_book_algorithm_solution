#include "gmock/gmock.h"
#include "graph.hpp"
using std::optional;
using ::testing::ElementsAreArray;

// NOTE: 最短経路のような導出となっている
void recursive_search(const vector<multiset<int>> &G, const int v, vector<optional<int>> &depths) {
  for (const auto n : G.at(v)) {
    if (!depths.at(n).has_value()) {
      depths.at(n) = depths.at(v).value() + 1;
      recursive_search(G, n, depths);
    }
  }
}

// E: 木 (連結, サイクルなし) TODO
vector<int> tree_depth(const multimap<int, int> &E, const int root) {
  using std::ranges::transform;

  const auto G = to_adjacency_list(E);

  vector<optional<int>> depths(G.size());
  depths.at(root) = 0;

  recursive_search(G, root, depths);

  // optionalはがし
  vector<int> results(G.size());
  transform(depths, results.begin(),
            [](const auto o) { return o.value(); }  // TODO: optional<auto> or auto
            );

  // TODO: C++23
  // using std::views::transform;
  // using std::ranges::to;

  return results;
}

// TODO: test case
TEST(TestSuite, Ex) {
  const multimap<int, int> T {
    {0, 1},
    {0, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    {4, 7},
    {4, 8},
    {2, 6},
    {6, 9},
  };

  EXPECT_THAT(tree_depth(T, 0), ElementsAreArray({0, 1, 1, 2, 2, 2, 2, 3, 3, 3}));
}
