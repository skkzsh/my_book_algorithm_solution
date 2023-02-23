#include "gtest/gtest.h"
#include "union-find.hpp"
#include "template.hpp"
#include <ranges>
using std::vector;

// R, T: 辺集合 (0以上の連番であること)
// N: 都市の数 (R, Tと整合が取れていること)
vector<int> cities(const Pairs<int> R, const Pairs<int> T, const int N) {
    using std::views::iota;
    // const int N = ;  // TODO
    UnionFind road_uf(N);
    UnionFind train_uf(N);

    for (const auto& e : R) {
        road_uf.unite(e.first, e.second);
    }
    for (const auto& e : T) {
        train_uf.unite(e.first, e.second);
    }

    vector<int> results(N, 0);

    for (const int u : iota(0, N)) {
        int count = 0;
        for (const int v : iota(0, N)) {
            if (road_uf.is_same_set(u, v) && train_uf.is_same_set(u, v)) {
                count++;
            }
        }
        results.at(u) = count;
    }

    return results;
}

TEST(TestCase, Ex1) {
    const Pairs<int> R {
        {0, 1},
        {1, 2},
        {2, 3},
    };
    const Pairs<int> T {
        {1, 2},
    };
    const vector<int> results = cities(R, T, 4);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 2);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 1);
}

TEST(TestCase, Ex2) {
    const Pairs<int> R {
        {0, 1},
        {1, 2},
    };
    const Pairs<int> T {
        {0, 3},
        {1, 2},
    };
    const vector<int> results = cities(R, T, 4);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 2);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 1);
}

TEST(TestCase, Ex3) {
    const Pairs<int> R {
        {0, 1},
        {1, 2},
        {1, 4},
        {5, 6},
    };
    const Pairs<int> T {
        {2, 4},
        {3, 4},
        {2, 3},
        {5, 6},
    };
    const vector<int> results = cities(R, T, 7);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 1);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 1);
    EXPECT_EQ(results.at(4), 2);
    EXPECT_EQ(results.at(5), 2);
    EXPECT_EQ(results.at(6), 2);
}
