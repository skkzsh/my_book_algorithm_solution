#pragma once

#include "template.hpp"

// TODO: 型の制約としたい
// E: 辺集合
// 頂点数 (位数) を返す
// ただし, 頂点が0以上の連番でない場合, 例外を投げる
// なお, 連結かどうかは判定してない
size_t graph_order(const Pairs<int> &E);
