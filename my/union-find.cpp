#include "union-find.hpp"
#include <stdexcept>

UnionFind::UnionFind(const int n) : parents(n), sizes(n, 1) {}

int UnionFind::root(const int x) {
    if (parents[x].has_value()) {
        parents[x] = root(parents[x].value()); // 経路圧縮
        return parents[x].value();
    }
    return x;
}

bool UnionFind::is_same_set(const int x, const int y) {
    return root(x) == root(y);
}

void UnionFind::unite(const int x, const int y) {
    const int root_x = root(x);
    const int root_y = root(y);

    if (root_x == root_y) {
        throw std::invalid_argument("Already same set");
    }

    // union by size
    if (sizes[root_x] < sizes[root_y]) {
        parents[root_x] = root_y;
        sizes[root_y] += sizes[root_x];
    } {
        parents[root_y] = root_x;
        sizes[root_x] += sizes[root_y];
    }
}

int UnionFind::size(const int x) {
    return sizes[root(x)];
}
