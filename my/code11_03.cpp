#include "gtest/gtest.h"
#include "union-find.hpp"

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
