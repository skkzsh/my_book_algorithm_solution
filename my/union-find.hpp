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
  int size(int v); // vの属する集合の要素数
 public:
  UnionFind(int N);
  int root(int v);
  bool is_same_set(int u, int v);
  bool unite(int u, int v);
  int count_set() const; // 集合の数
};
