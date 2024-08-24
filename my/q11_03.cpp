#include "gmock/gmock.h"
#include "union-find.hpp"
#include "template.hpp"
#include <ranges>

using ::testing::ElementsAreArray;
using std::views::transform;
using std::ranges::to;

constexpr vector<int> roots(const int v, const vector<UnionFind> &ufs) {
  return ufs | transform([v](UnionFind uf) { return uf.root(v); })
             | to<vector>();
}

// E: 辺集合 (0以上の連番であること)
// N: 都市の数 (Eと整合が取れていること)
// TODO: constexpr (C++23)
vector<int> cities(const vector<Pairs<int>> &E, const int N) {
  using std::views::iota;
  // using std::views::enumerate;
  using std::map;

  // const int N = ;  // TODO
  vector<UnionFind> ufs(E.size(), N);

  // for (const auto &[i, e] : E | enumerate) {
  for (const auto i : iota(0u, E.size())) {
    for (const auto &[u, v] : E.at(i)) {
      ufs.at(i).unite(u, v);
    }
  }

  map<vector<int>, int> counts;
  for (const auto v : iota(0, N)) {
    ++counts[roots(v, ufs)]; // at を使えない
  }

  // for (const int u : iota(0, N)) {
  //     int count = 0;
  //     for (const int v : iota(0, N)) {
  //         if (all_of(ufs, [&](UnionFind uf) {
  //             return uf.is_same_set(u, v);
  //         })) {
  //             ++count;
  //         }
  //     }
  //     results.at(u) = count;
  // }

  return iota(0, N) | transform([=](const int v) { return counts.at(roots(v, ufs)); })
                    | to<vector>();
}


const struct TestParam {
  const vector<Pairs<int>> E;
  const int N;
  const vector<int> gold;
} PARAMS[] {
  {
    {
      { {0, 1}, {1, 2}, {2, 3}, },
      { {1, 2}, },
    },
    4,
    {1, 2, 2, 1},
  },
  {
    {
      { {0, 1}, {1, 2}, },
      { {0, 3}, {1, 2}, },
    },
    4,
    {1, 2, 2, 1},
  },
  {
    {
      { {0, 1}, {1, 2}, {1, 4}, {5, 6}, },
      { {2, 4}, {3, 4}, {2, 3}, {5, 6}, },
    },
    7,
    {1, 1, 2, 1, 2, 2, 2},
  },
};

class TestSuite : public testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_THAT(cities(GetParam().E, GetParam().N), ElementsAreArray(GetParam().gold));
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    testing::ValuesIn(PARAMS)
                         );
