#include "gmock/gmock.h"
#include "graph.hpp"
#include <ranges>
#include <list>
using ::testing::ElementsAreArray;
using std::list;

// TODO: BFS

constexpr void recursive_search(const vector<multiset<int>> &G, const int v, vector<bool> &seen, list<int> &order) {
  seen.at(v) = true;

  for (const auto n : G.at(v)) {
    if (!seen.at(n)) {
      recursive_search(G, n, seen, order);
    }
  }

  order.push_back(v); // 帰りがけ
}

constexpr list<int> topological_sort_by_recursive(const multimap<int, int> &E) {
  using std::views::iota;

  const auto G = to_adjacency_list(E, true);

  vector<bool> seen(G.size());
  list<int> order;

  for (const auto v : iota(0, static_cast<int>(G.size()))) {
    if (!seen.at(v)) {
      recursive_search(G, v, seen, order);
    }
  }

  order.reverse();
  return order;
}

TEST(TestSuite, Ex) {
  const multimap<int, int> E {
    {0, 5},
    {1, 3},
    {1, 6},
    {2, 5},
    {2, 7},
    {3, 0},
    {3, 7},
    {4, 1},
    {4, 2},
    {4, 6},
    {6, 7},
    {7, 0},
  };

  // 解はひとつでない
  EXPECT_THAT(topological_sort_by_recursive(E), ElementsAreArray({4, 2, 1, 6, 3, 7, 0, 5}));
}
