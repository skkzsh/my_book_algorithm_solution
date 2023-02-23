#include "union-find.hpp"
#include <stdexcept>

UnionFind::UnionFind(const int n) : parents(n), sizes(n, 1) {}

int UnionFind::root(const int x) {
    if (parents.at(x).has_value()) {
        parents.at(x) = root(parents.at(x).value()); // 経路圧縮
        return parents.at(x).value();
    }
    return x;
}

bool UnionFind::is_same_set(const int x, const int y) {
    return root(x) == root(y);
}

bool UnionFind::unite(const int x, const int y) {
    const int root_x = root(x);
    const int root_y = root(y);

    if (root_x == root_y) {
        return false;
    }

    // union by size
    if (sizes.at(root_x) < sizes.at(root_y)) {
        parents.at(root_x) = root_y;
        sizes.at(root_y) += sizes.at(root_x);
    } {
        parents.at(root_y) = root_x;
        sizes.at(root_x) += sizes.at(root_y);
    }

    return true;
}

int UnionFind::size(const int x) {
    return sizes[root(x)];
}
