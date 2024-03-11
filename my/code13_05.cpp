#include "gtest/gtest.h"
#include "graph.hpp"
using std::optional;

// 2部グラフの分類
typedef enum {
  RED  = 0,
  BLUE = 1,
} COLOR;

bool recursive_search(const vector<unordered_multiset<int>> &G, const int v, vector<optional<COLOR>> &color) {
  color.at(v) = RED;

  for (const auto n : G.at(v)) {
    if (!color.at(n).has_value()) {
      recursive_search(G, n, color);
    } else if (color.at(n) == RED) {
      return false;
    }
  }
  return true;
}

bool is_bipartite_by_recursive(const unordered_multimap<int, int> &E) {
  const auto G = to_adjacency_list(E);

  vector<optional<COLOR>> colors(G.size());

  return recursive_search(G, 0, colors);
}

TEST(TestSuite, Ex) {
  const unordered_multimap<int, int> E {
    {0, 1},
    {0, 3},
    {1, 2},
    {1, 4},
    {3, 4},
  };

  GTEST_SKIP() << "実装中のため"; // TODO
  EXPECT_TRUE(is_bipartite_by_recursive(E));
}