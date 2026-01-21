#pragma once

#include "template.hpp" // TODO
#include <map>
#include <set>
#include <queue>
#include <stack>
using std::multimap;
using std::multiset;
using std::map;
using std::set;
using std::pair;

// TODO: クラス化したい

// E: 辺集合
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない (辺のない頂点が存在する) 場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t order_edge_set(const multimap<int, int> &E);

// 辺集合 (重みなし) を隣接リスト表現に変換する
// is_direct: 有向グラフかどうか
vector<multiset<int>> to_adjacency_list(const multimap<int, int> &E, const bool is_direct = false);

// 辺集合 (重みあり, 有向グラフ) を隣接リスト表現に変換する
vector<map<int, int>> to_adjacency_list(const map<pair<int, int>, int> &E);

void recursive_search(const vector<multiset<int>> &G, const int v, vector<bool> &seen);

void bfs(const vector<multiset<int>> &G, const int v, vector<bool> &seen);
