#include "gtest/gtest.h"
#include "union-find.hpp"
#include "template.hpp"
#include <ranges>

// E: 辺集合 (連結かつ0以上の連番であること)
// N: 頂点数 (Gと整合が取れていること)
int bridges(const Pairs<int> E, const int N) {
    auto edge_view = std::views::iota(0, (int) E.size());
    // const int N = ;  // TODO
    int count = 0;

    for (const int j : edge_view) {
        UnionFind uf(N);

        for (const int i : edge_view) {
            if (i != j) {
                uf.unite(E.at(i).first, E.at(i).second);
            }
        }

        if (uf.count_set() > 1) {
             ++count;
        }
    }

    return count;
}

TEST(TestSuite, Ex1) {
    const Pairs<int> E {
        {0, 2},
        {1, 6},
        {2, 3},
        {3, 4},
        {3, 5},
        {4, 5},
        {5, 6},
    };

    EXPECT_EQ(bridges(E, 7), 4);
}

TEST(TestSuite, Ex2) {
    const Pairs<int> E {
        {2, 2},
        {0, 1},
        {0, 2},
        {1, 2},
    };

    EXPECT_EQ(bridges(E, 3), 0);
}

TEST(TestSuite, Ex3) {
    const Pairs<int> E {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
    };

    EXPECT_EQ(bridges(E, 6), 5);
}
