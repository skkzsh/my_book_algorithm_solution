#pragma once

#include <vector>
// #include "template.hpp" // TODO

// TODO: 型の制約としたい

// E: 辺集合
// 0以上の連番であること (連結であること) を検証する
// 連結の場合, 頂点数を返す
// TODO: Pairs
// int vertex_num_of_connected_graph(const Pairs<int> &E);
size_t vertex_num_of_connected_graph(const std::vector<std::pair<int, int>> &E);
