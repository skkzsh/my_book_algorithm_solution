#include "graph.hpp"
#include <stdexcept>
#include <format>

// TODO: test

using std::invalid_argument;
using std::format;

// ただし, 頂点が0以上の連番でない場合, 例外を投げる
// なお, 連結かどうかは判定してない
EdgeSet::EdgeSet(const Pairs<int> &P) : P(P) {
  using std::next;

  for (const auto &[u, v] : P) {
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
}

size_t EdgeSet::size() const {
  return P.size();  // 委譲
}

pair<int, int> EdgeSet::at(const int i) const {
  return P.at(i);  // 委譲
}

size_t EdgeSet::order() const {
  return V.size();
}

vector<vector<int>> EdgeSet::to_adjacency_list() const {
  vector<vector<int>> G(order()); // 隣接リスト表現
  // vector<vector<int>> G(order(), vector<int>(size())); // 隣接リスト表現

  for (const auto &[u, v] : P) {
    G.at(u).push_back(v);
    G.at(v).push_back(u); // 無向グラフ
  }

  return G;
}
