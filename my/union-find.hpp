#pragma once

#include <vector>
#include <optional>
using std::vector;
using std::optional;

class UnionFind {
    private:
        vector<optional<int>> parents;
        vector<int> sizes;
    public:
        UnionFind(const int n);
        int root(const int v);
        bool is_same_set(const int u, const int v);
        bool unite(const int u, const int v);
    private:
        int size(int v);
};
