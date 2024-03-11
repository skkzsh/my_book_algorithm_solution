#pragma once

#include "template.hpp" // TODO
#include <vector>
#include <unordered_map>
#include <unordered_set>
// #include <map>
// #include <set>using std::vector;
using std::unordered_multimap;
using std::unordered_multiset;
// using std::multimap;
// using std::multiset;

// TODO: クラス化したい

// E: 辺集合
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t order_edge_set(const unordered_multimap<int, int>& E);

// 辺集合を隣接リスト表現に変換する
// is_direct: 有向グラフかどうか
vector<unordered_multiset<int>> to_adjacency_list(const unordered_multimap<int, int>& E, const bool is_direct = false);
