#include "gtest/gtest.h"
#include "template.hpp"
#include "union-find.hpp"

// G: グラフ (連結かつ0以上の連番であること)
// N: 頂点数 (Gと整合が取れていること)
int bridges(const Pairs<int> G, const int N) {
    // const int N = ;  // TODO
    int count = 0;

    for (size_t j = 0; j < G.size(); ++j) {
        UnionFind uf(N);

        for (size_t i = 0; i < G.size(); ++i) {
            if (i != j) {
                uf.unite(G.at(i).first, G.at(i).second);
            }
        }

        if (uf.count_set() > 1) {
             ++count;
        }
    }

    return count;
}

TEST(TestCase, Ex1) {
    const Pairs<int> G {
        {0, 2},
        {1, 6},
        {2, 3},
        {3, 4},
        {3, 5},
        {4, 5},
        {5, 6},
    };

    EXPECT_EQ(bridges(G, 7), 4);
}

TEST(TestCase, Ex2) {
    const Pairs<int> G {
        {2, 2},
        {0, 1},
        {0, 2},
        {1, 2},
    };

    EXPECT_EQ(bridges(G, 3), 0);
}

TEST(TestCase, Ex3) {
    const Pairs<int> G {
        {0, 1},
        {1, 2},
        {2, 3},
        {3, 4},
        {4, 5},
    };

    EXPECT_EQ(bridges(G, 6), 5);
}
