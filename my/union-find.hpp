#ifndef UNION_FIND_H
#define UNION_FIND_H

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
    private:
        int root(const int x);
    public:
        bool is_same_set(const int x, const int y);
        void unite(const int x, const int y);
    private:
        int size(int x);
};

#endif
