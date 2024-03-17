#include "graph.hpp"
#include <set>
#include <stdexcept>
#include <format>

// TODO: test

size_t order_edge_set(const multimap<int, int>& E) {
  using std::set;
  using std::next;
  using std::invalid_argument;
  using std::format;

  set<int> V; // 頂点集合
  for (const auto &[u, v] : E) {
    V.insert(u);
    V.insert(v);
  }

  if (!V.empty()) {
    auto prev = V.begin();

    if (*prev != 0) {
      throw invalid_argument("Minimum number of element must be zero");
    }

    if (V.size() > 1) {
      for (auto curr = next(prev); curr != V.end(); ++prev, ++curr) {
        if (*curr - *prev != 1) {
          throw invalid_argument(format("Elements must be sequential: {} -> {}", *prev, *curr));
        }
      }
    }
  }

  return V.size();
}

vector<multiset<int>> to_adjacency_list(const multimap<int, int>& E, const bool is_direct) {
  const auto N = order_edge_set(E);

  vector<multiset<int>> G(N);

  for (const auto &[u, v] : E) {
    G.at(u).insert(v);
    if (!is_direct) {
      G.at(v).insert(u); // 無向グラフ
    }
  }

  return G;
}

void recursive_search(const vector<multiset<int>> &G, const int v, vector<bool> &seen) {
  seen.at(v)= true;

  for (const auto n : G.at(v)) {
    if (!seen.at(n)) {
      recursive_search(G, n, seen);
    }
  }
}

void bfs(const vector<multiset<int>> &G, const int v, vector<bool> &seen) {
  std::queue<int> todo; // BFS

  seen.at(v) = true;
  todo.push(v);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();

    for (const auto n : G.at(v)) {
      if (!seen.at(n)) {
        seen.at(n) = true;
        todo.push(n);
      }
    }
  }
}
