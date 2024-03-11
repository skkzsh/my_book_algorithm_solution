#include "graph.hpp"
#include <set>
#include <stdexcept>

size_t graph_order(const Pairs<int> &E) {
  using std::next;
  using std::invalid_argument;

  std::set<int> V; // 頂点集合
  for (const auto &[u, v] : E) {
    V.insert(u);
    V.insert(v);
  }

  if (!V.empty()) {
    auto prev = V.begin();

    if (*prev != 0) {
      throw invalid_argument("Minimum number of vertex must be zero");
    }

    if (V.size() > 1) {
      for (auto curr = next(prev); curr != V.end(); ++prev, ++curr) {
        if (*curr - *prev != 1) {
          throw invalid_argument("Vertex must be sequential");
        }
      }
    }
  }

  return V.size();
}
