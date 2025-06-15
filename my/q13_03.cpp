#include "gtest/gtest.h"
#include "graph.hpp"
#include <queue>
#include <stack>
using std::optional;

// 2部グラフの分類
typedef enum {
  RED  = 0,
  BLUE = 1,
} COLOR;

constexpr bool recursive_search(const vector<multiset<int>> &G, const int v, const COLOR prev, vector<optional<COLOR>> &colors) {
  auto const curr = prev == RED ? BLUE : RED;
  colors.at(v) = curr;

  for (const auto n : G.at(v)) {
    if (colors.at(n).has_value()) {
      if (colors.at(n).value() == curr) {
        return false;
      }
    } else {
      if (!recursive_search(G, n, curr, colors)) {
        return false;
      }
    }
  }
  return true;
}

constexpr bool is_bipartite_by_recursive(const multimap<int, int> &E) {
  const auto G = to_adjacency_list(E);

  vector<optional<COLOR>> colors(G.size());

  return recursive_search(G, 0, RED, colors);
}

constexpr bool is_bipartite_by_bfs(const multimap<int, int> &E) {
  const auto G = to_adjacency_list(E);

  vector<optional<COLOR>> colors(G.size());
  std::queue<int> todo; // BFS

  // 初期化: 0に赤色を塗るとしても, 一般性を失わない
  colors.at(0) = RED;
  todo.push(0);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();
    const auto curr = colors.at(v);

    for (const auto n : G.at(v)) {
      if (colors.at(n).has_value()) {
        if (colors.at(n).value() == curr) {
          return false;
        }
      } else {
        colors.at(n) = curr == RED ? BLUE : RED;
        todo.push(n);
      }
    }
  }

  return true;
}

TEST(TestSuite, Bipartite) {
  const multimap<int, int> E {
    {0, 1},
    {0, 3},
    {1, 2},
    {1, 4},
    {3, 4},
  };
  EXPECT_TRUE(is_bipartite_by_recursive(E));
  EXPECT_TRUE(is_bipartite_by_bfs(E));
}

TEST(TestSuite, NotBipartite) {
  const multimap<int, int> E {
    {0, 1},
    {0, 3},
    {1, 2},
    {1, 4},
    {3, 4},
    {2, 4}, // 2部グラフじゃなくする
  };
  EXPECT_FALSE(is_bipartite_by_recursive(E));
  EXPECT_FALSE(is_bipartite_by_bfs(E));
}
