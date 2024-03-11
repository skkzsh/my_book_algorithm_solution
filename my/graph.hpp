#pragma once

#include "template.hpp"
#include <vector>
using std::vector;

// TODO: 型の制約としたい

// E: 辺集合
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t order_edge_set(const Pairs<int>& E);

// G: 隣接リスト
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t order_adjacency_list(const vector<vector<int>>& G);

// G: 隣接リスト
// 無向グラフとして整合しているかを検証する (2->5があるなら5->2があること)
// なお, 連結かどうかは判定してない
void validate_undirected(const vector<vector<int>>& G);
