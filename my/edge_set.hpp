#pragma once

#include "template.hpp"
#include <vector>
#include <set>
using std::vector;
using std::set;

// 辺集合
class EdgeSet {
 public:
  EdgeSet(const Pairs<int>& P);
  size_t size() const; // 辺数
  pair<int, int> at(const int i) const;
  size_t order() const; // 頂点数 (位数)
  vector<vector<int>> to_adjacency_list() const; // 隣接リスト表現
 private:
  const Pairs<int> P;
  set<int> V; // 頂点集合
};
