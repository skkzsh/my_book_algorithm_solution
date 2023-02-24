#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "union-find.hpp"
#include "template.hpp"
using ::testing::ElementsAreArray;
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

TEST(TestSuite, Ex1) {
    const Pairs<int> E {
        {0, 1},
        {2, 3},
        {0, 2},
        {1, 2},
        {0, 3},
    };
    EXPECT_THAT(decay(E, 4), ElementsAreArray({1, 1, 2, 3, 4}));
}

TEST(TestSuite, Ex2) {
    const Pairs<int> E {
        {1, 2},
        {0, 1},
        {4, 5},
        {2, 3},
        {3, 4},
    };
    EXPECT_THAT(decay(E, 6), ElementsAreArray({2, 3, 4, 5, 6}));
}

TEST(TestSuite, Ex3) {
    EXPECT_THAT(decay({{0, 1}}, 2), ElementsAreArray({2}));
}
