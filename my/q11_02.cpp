#include "gtest/gtest.h"
#include "union-find.hpp"
#include "template.hpp"
using std::vector;

// E: 辺集合 (0以上の連番であること)
// N: 頂点数 (Gと整合が取れていること)
vector<int> decay(const Pairs<int> E, const int N) {
    // const int N = ;  // TODO
    UnionFind uf(N);
    vector<int> results(E.size(), 0);

    for (int e = (int) E.size() - 1; e >= 0; --e) {
        results.at(e) = uf.count_set();
        uf.unite(E.at(e).first, E.at(e).second);
    }

    return results;
}

TEST(TestCase, Ex1) {
    const Pairs<int> E {
        {0, 1},
        {2, 3},
        {0, 2},
        {1, 2},
        {0, 3},
    };
    const vector<int> results = decay(E, 4);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 1);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 3);
    EXPECT_EQ(results.at(4), 4);
}

TEST(TestCase, Ex2) {
    const Pairs<int> E {
        {1, 2},
        {0, 1},
        {4, 5},
        {2, 3},
        {3, 4},
    };
    const vector<int> results = decay(E, 6);
    EXPECT_EQ(results.at(0), 2);
    EXPECT_EQ(results.at(1), 3);
    EXPECT_EQ(results.at(2), 4);
    EXPECT_EQ(results.at(3), 5);
    EXPECT_EQ(results.at(4), 6);
}

TEST(TestCase, Ex3) {
    EXPECT_EQ(decay({{0, 1}}, 2).at(0), 2);
}
