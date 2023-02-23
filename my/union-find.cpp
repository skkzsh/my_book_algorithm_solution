#include "union-find.hpp"
#include <stdexcept>
#include <utility>

UnionFind::UnionFind(const int n) : parents(n), sizes(n, 1) {}

int UnionFind::root(const int v) {
    if (!parents.at(v).has_value()) {
        return v;
    }

    parents.at(v) = root(parents.at(v).value()); // 経路圧縮
    return parents.at(v).value();
}

bool UnionFind::is_same_set(const int u, const int v) {
    return root(u) == root(v);
}

bool UnionFind::unite(const int u, const int v) {
    int root_u = root(u);
    int root_v = root(v);

    if (root_u == root_v) {
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
