#include "graph.hpp"
#include <set>
#include <ranges>
#include <stdexcept>
#include <format>

// TODO: test

using std::set;
using std::invalid_argument;
using std::format;

// private
void validate_seq_set(const set<int>& V) {
  using std::next;

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
}

size_t order_edge_set(const Pairs<int>& E) {
  set<int> V; // 頂点集合
  for (const auto &[u, v] : E) {
    V.insert(u);
    V.insert(v);
  }

  validate_seq_set(V);

  return V.size();
}

size_t order_adjacency_list(const vector<vector<int>>& G) {
  set<int> V; // 頂点集合
  for (const auto& d : G) {
    for (const auto v : d) {
      V.insert(v);
    }
  }

  validate_seq_set(V);

  return V.size();
}

void validate_undirected(const vector<vector<int>>& G) {
  using std::views::iota;
  using std::ranges::find;

  for (const auto u : iota(0u, G.size())) {
    for (const auto v : G.at(u)) {
      if (const auto& d = G.at(v); find(d, u) == d.end()) {
        throw invalid_argument(format("Inconsistent as undirected graph: {} -> {}", u, v));
      }
    }
  }
}
