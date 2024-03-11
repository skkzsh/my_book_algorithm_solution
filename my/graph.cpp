#include "graph.hpp"
#include <set>
#include <stdexcept>

// TODO: test

using std::set;

// private
void validate_seq_set(const set<int> &V) {
  using std::next;
  using std::invalid_argument;

  if (!V.empty()) {
    auto prev = V.begin();

    if (*prev != 0) {
      throw invalid_argument("Minimum number of element must be zero");
    }

    if (V.size() > 1) {
      for (auto curr = next(prev); curr != V.end(); ++prev, ++curr) {
        if (*curr - *prev != 1) {
          throw invalid_argument("Elements must be sequential");
        }
      }
    }
  }
}

size_t order_edge_set(const Pairs<int> &E) {
  set<int> V; // 頂点集合
  for (const auto &[u, v] : E) {
    V.insert(u);
    V.insert(v);
  }

  validate_seq_set(V);

  return V.size();
}

size_t order_adjacency_list(const vector<vector<int>> &G) {
  set<int> V; // 頂点集合
  for (const auto &d : G) {
    for (const auto v : d) {
      V.insert(v);
    }
  }

  validate_seq_set(V);

  return V.size();
}
