#pragma once

#include "template.hpp" // TODO
#include <map>
#include <set>
using std::multimap;
using std::multiset;

// TODO: クラス化したい

// E: 辺集合
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない (辺のない頂点が存在する) 場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t order_edge_set(const multimap<int, int>& E);

// 辺集合を隣接リスト表現に変換する
// is_direct: 有向グラフかどうか
vector<multiset<int>> to_adjacency_list(const multimap<int, int>& E, const bool is_direct = false);
