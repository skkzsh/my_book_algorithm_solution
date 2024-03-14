#include "gtest/gtest.h"
#include "graph.hpp"
using std::optional;

// 2部グラフの分類
typedef enum {
  RED  = 0,
  BLUE = 1,
} COLOR;

bool recursive_search(const vector<multiset<int>> &G, const int v, const COLOR prev, vector<optional<COLOR>> &colors) {
  auto const curr = prev == RED ? BLUE : RED;
  colors.at(v) = curr;

  for (const auto n : G.at(v)) {
    if (!colors.at(n).has_value()) {
      if (!recursive_search(G, n, curr, colors)) {
        return false;
      }
    } else if (colors.at(n).value() == curr) {
      return false;
    }
  }
  return true;
}

bool is_bipartite_by_recursive(const multimap<int, int> &E) {
  const auto G = to_adjacency_list(E);

  vector<optional<COLOR>> colors(G.size());

  return recursive_search(G, 0, RED, colors);
}

TEST(TestSuite, Bipartite) {
  EXPECT_TRUE(is_bipartite_by_recursive({
    {0, 1},
    {0, 3},
    {1, 2},
    {1, 4},
    {3, 4},
    }));
}

TEST(TestSuite, NotBipartite) {
  EXPECT_FALSE(is_bipartite_by_recursive({
    {0, 1},
    {0, 3},
    {1, 2},
    {1, 4},
    {3, 4},
    {2, 4}, // 2部グラフじゃなくする
    }));
}
