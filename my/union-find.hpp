#pragma once

#include <vector>
#include <optional>
using std::vector;
using std::optional;

class UnionFind {
 private:
  const int N; // 要素数
  vector<optional<int>> parents;
  vector<int> sizes; // 各要素の属する集合の要素数
  int size(const int v); // vの属する集合の要素数
 public:
  UnionFind(const int N);
  int root(const int v);
  bool is_same_set(const int u, const int v);
  bool unite(const int u, const int v);
  int count_set() const; // 集合の数
};
