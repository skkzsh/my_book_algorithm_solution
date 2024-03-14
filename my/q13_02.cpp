#include "gtest/gtest.h"
#include "graph.hpp"
#include <queue>
#include <stack>
using std::pair;

// E: 辺集合
// p: {s, t}

void recursive_search(const vector<multiset<int>> &G, const int v, vector<bool> &seen) {
  seen.at(v)= true;

  for (const auto n : G.at(v)) {
    if (!seen.at(n)) {
      recursive_search(G, n, seen);
    }
  }
}

bool exists_path_by_recursive(const multimap<int, int> &E, const pair<int, int> &p) {
  const auto G = to_adjacency_list(E, true);
  const auto [s, t] = p;

  vector<bool> seen(G.size());

  recursive_search(G, s, seen);

  return seen.at(t);
}

bool exists_path_by_bfs(const multimap<int, int> &E, const pair<int, int> &p) {
  const auto G = to_adjacency_list(E, true);
  const auto [s, t] = p;

  vector<bool> seen(G.size());
  std::queue<int> todo; // BFS

  seen.at(s) = true;
  todo.push(s);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();

    for (const auto n : G.at(v)) {
      if (n == t) {
        return true;
      }
      if (!seen.at(n)) {
        seen.at(n) = true;
        todo.push(n);
      }
    }

  }

  return false;
}

TEST(TestSuite, PathExists) {
  const multimap<int, int> E {
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

  EXPECT_TRUE(exists_path_by_recursive(E, {0, 7}));
  EXPECT_TRUE(exists_path_by_bfs(E, {0, 7}));
}

TEST(TestSuite, PathNotExists) {
  const multimap<int, int> E {
      {0, 1},
      {0, 2},
      {0, 4},
      {1, 3},
      {1, 4},
      {1, 8},
      {2, 5},
      // {3, 7}, // tを孤立させる
      {3, 8},
      {4, 8},
      // {5, 6}, // tを孤立させる
      {5, 8},
      {6, 7},
    };

  EXPECT_FALSE(exists_path_by_recursive(E, {0, 7}));
  EXPECT_FALSE(exists_path_by_bfs(E, {0, 7}));
}
