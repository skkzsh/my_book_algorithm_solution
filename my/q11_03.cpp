#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "union-find.hpp"
#include "template.hpp"
#include <ranges>
#include <algorithm>
#include <map>
using ::testing::ElementsAreArray;
using std::vector;

vector<int> roots(const int v, vector<UnionFind> ufs) {
    vector<int> results(ufs.size());

    for (UnionFind uf : ufs) {
        results.push_back(uf.root(v));
    }

    return results;
}

// E: 辺集合 (0以上の連番であること)
// N: 都市の数 (Eと整合が取れていること)
vector<int> cities(const vector<Pairs<int>> E, const int N) {
    using std::views::iota;
    using std::map;

    // const int N = ;  // TODO
    vector<UnionFind> ufs(E.size(), N);

    for (size_t i = 0; i < E.size(); ++i) {
        for (const auto& e : E.at(i)) {
            ufs.at(i).unite(e.first, e.second);
        }
    }

    map<vector<int>, int> counts;
    for (const int v : iota(0, N)) {
        counts[roots(v, ufs)]++;
    }

    vector<int> results(N);
    for (const int v : iota(0, N)) {
        results.at(v) = counts[roots(v, ufs)];
    }

    // for (const int u : iota(0, N)) {
    //     int count = 0;
    //     for (const int v : iota(0, N)) {
    //         if (all_of(ufs, [&](UnionFind uf) {
    //             return uf.is_same_set(u, v);
    //         })) {
    //             count++;
    //         }
    //     }
    //     results.at(u) = count;
    // }

    return results;
}

TEST(TestCase, Ex1) {
    const vector<Pairs<int>> E {
        { {0, 1}, {1, 2}, {2, 3}, },
        { {1, 2}, },
    };
    EXPECT_THAT(cities(E, 4), ElementsAreArray({1, 2, 2, 1}));
}

TEST(TestCase, Ex2) {
    const vector<Pairs<int>> E {
        { {0, 1}, {1, 2}, },
        { {0, 3}, {1, 2}, },
    };
    EXPECT_THAT(cities(E, 4), ElementsAreArray({1, 2, 2, 1}));
}

TEST(TestCase, Ex3) {
    const vector<Pairs<int>> E {
        { {0, 1}, {1, 2}, {1, 4}, {5, 6}, },
        { {2, 4}, {3, 4}, {2, 3}, {5, 6}, },
    };
    EXPECT_THAT(cities(E, 7), ElementsAreArray({1, 1, 2, 1, 2, 2, 2}));
}
