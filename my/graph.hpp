#pragma once

#include "template.hpp"

// E: 辺集合
// 0以上の連番であること (連結であること) を検証する
// 連結の場合, 頂点数を返す
size_t vertex_num_of_connected_graph(const Pairs<int> &E);
