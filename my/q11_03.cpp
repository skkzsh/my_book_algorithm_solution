#include "gtest/gtest.h"
#include "union-find.hpp"
#include "template.hpp"
#include <ranges>
#include <algorithm>
using std::vector;

// E: 辺集合 (0以上の連番であること)
// N: 都市の数 (Eと整合が取れていること)
vector<int> cities(const vector<Pairs<int>> E, const int N) {
    using namespace std::ranges;
    using std::views::iota;
    // const int N = ;  // TODO
    vector<UnionFind> ufs(E.size(), N);

    for (size_t i = 0; i < E.size(); ++i) {
        for (const auto& e : E.at(i)) {
            ufs.at(i).unite(e.first, e.second);
        }
    }

    vector<int> results(N);

    transform(iota(0, N), results.begin(), [&](const int u) {
        return count_if(iota(0, N), [&](const int v) {
            return all_of(ufs, [&](UnionFind uf) { return uf.is_same_set(u, v); });
        });
    });

    return results;
}

TEST(TestCase, Ex1) {
    const vector<Pairs<int>> E {
        { {0, 1}, {1, 2}, {2, 3}, },
        { {1, 2}, },
    };
    const vector<int> results = cities(E, 4);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 2);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 1);
}

TEST(TestCase, Ex2) {
    const vector<Pairs<int>> E {
        { {0, 1}, {1, 2}, },
        { {0, 3}, {1, 2}, },
    };
    const vector<int> results = cities(E, 4);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 2);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 1);
}

TEST(TestCase, Ex3) {
    const vector<Pairs<int>> E {
        { {0, 1}, {1, 2}, {1, 4}, {5, 6}, },
        { {2, 4}, {3, 4}, {2, 3}, {5, 6}, },
    };
    const vector<int> results = cities(E, 7);
    EXPECT_EQ(results.at(0), 1);
    EXPECT_EQ(results.at(1), 1);
    EXPECT_EQ(results.at(2), 2);
    EXPECT_EQ(results.at(3), 1);
    EXPECT_EQ(results.at(4), 2);
    EXPECT_EQ(results.at(5), 2);
    EXPECT_EQ(results.at(6), 2);
}
