#include "union-find.hpp"
#include <ranges>
#include <algorithm>
#include <utility>

UnionFind::UnionFind(const int N) : N(N), parents(N), sizes(N, 1) {}

int UnionFind::root(const int v) {
    if (!parents.at(v).has_value()) {
        return v;  // 親がいないなら, 自身が根
    }

    parents.at(v) = root(parents.at(v).value()); // 経路圧縮
    return parents.at(v).value();
}

bool UnionFind::is_same_set(const int u, const int v) {
    return root(u) == root(v);  // 根が同じなら同じ集合
}

bool UnionFind::unite(const int u, const int v) {
    int root_u = root(u);
    int root_v = root(v);

    if (root_u == root_v) {  // すでに同じ集合なら何もしない
        return false;
    }

    // union by size
    if (sizes.at(root_u) < sizes.at(root_v)) {
        std::swap(root_u, root_v);
    }

    parents.at(root_v) = root_u;
    sizes.at(root_u) += sizes.at(root_v);

// TODO
//    if (sizes.at(root_u) < sizes.at(root_v)) {
//        parents.at(root_u) = root_v;
//        sizes.at(root_v) += sizes.at(root_u);
//    } {
//        parents.at(root_v) = root_u;
//        sizes.at(root_u) += sizes.at(root_v);
//    }

    return true;
}

int UnionFind::size(const int v) {
    return sizes[root(v)];
}

int UnionFind::count_set() const {
    using std::ranges::count_if;
    using std::views::iota;

    // 根の数を数える
    return count_if(iota(0, N), [this](const int v){
        return !parents.at(v).has_value(); // 親がいないなら, 自身が根
    });
}
