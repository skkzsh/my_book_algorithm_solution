#include "graph.hpp"
#include <set>
#include <stdexcept>

// TODO: 型の制約としたい
size_t vertex_num_of_connected_graph(const Pairs<int> &E) {
  using std::invalid_argument;

  std::set<int> V; // 頂点集合
  for (const auto &[u, v] : E) {
    V.insert(u);
    V.insert(v);
  }

  auto prev = V.begin();
  auto curr = std::next(prev);

  if (*prev != 0) {
    throw invalid_argument("Minimum number of vertex must be zero");
  }

  for (; curr != V.end(); ++prev, ++curr) {
    if (*curr - *prev != 1) {
      throw invalid_argument("Vertex set is NOT sequential");
    }
  }

  return V.size();
}
