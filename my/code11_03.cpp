#include "gtest/gtest.h"
// #include "union-find.hpp"

using std::vector;
using std::optional;

class UnionFind {
    private:
        vector<optional<int>> parents;
        vector<int> sizes;

    public:
        UnionFind(const int n) : parents(n), sizes(n, 1) {}

    private:
        int root(const int x) {
            if (parents[x].has_value()) {
                parents[x] = root(parents[x].value()); // 経路圧縮
                return parents[x].value();
            }
            return x;
        }

    public:
        bool is_same_set(const int x, const int y) {
            return root(x) == root(y);
        }

        void unite(const int x, const int y) {
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

    private:
        int size(int x) {
            return sizes[root(x)];
        }

};

TEST(TestCase, Ex) {
    UnionFind uf(7); // {0}, {1}, {2}, {3}, {4}, {5}, {6}

    uf.unite(1, 2); // {0}, {1, 2}, {3}, {4}, {5}, {6}
    uf.unite(2, 3); // {0}, {1, 2, 3}, {4}, {5}, {6}
    uf.unite(5, 6); // {0}, {1, 2, 3}, {4}, {5, 6}
    EXPECT_EQ(uf.is_same_set(1, 3), true);
    EXPECT_EQ(uf.is_same_set(2, 5), false);

    uf.unite(1, 6); // {0}, {1, 2, 3, 5, 6}, {4}
    EXPECT_EQ(uf.is_same_set(2, 5), true);
}
