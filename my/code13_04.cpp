#include "gtest/gtest.h"
#include "graph.hpp"
#include <stack>
using std::pair;

// E: 辺集合
// p: {s, t}
bool exists_path(const Pairs<int> &E, const pair<int, int> &p) {
  using std::vector;

  const vector<vector<int>> G = to_adjacency_list(E, true);
  const auto [s, t] = p;

  vector<bool> seen(G.size());
  std::stack<int> todo;

  seen.at(s) = true;
  todo.push(s);

  while (!todo.empty()) {
    const auto v = todo.top();
    todo.pop();

    for (const auto x : G.at(v)) {
      if (x == t) {
        return true;
      }
      if (!seen.at(x)) {
        seen.at(x) = true;
        todo.push(x);
      }
    }

  }

  return false;
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

  EXPECT_TRUE(exists_path(E, {0, 7}));
}
