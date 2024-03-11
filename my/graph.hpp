#pragma once

#include "template.hpp"
#include <vector>
using std::vector;

// TODO: クラス化したい

// E: 辺集合
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t order_edge_set(const Pairs<int>& E);

// 辺集合を隣接リスト表現に変換する
vector<vector<int>> to_adjacency_list(const Pairs<int>& E);
