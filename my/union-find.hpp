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
        int root(const int x);
        bool is_same_set(const int x, const int y);
        bool unite(const int x, const int y);
    private:
        int size(int x);
};
