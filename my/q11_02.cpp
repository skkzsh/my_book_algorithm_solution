#include "gmock/gmock.h"
#include "union-find.hpp"
#include "graph.hpp"
#include <ranges>
using ::testing::ElementsAreArray;

// E: 辺集合 (0以上の連番であること)
vector<int> decay(const Pairs<int> &E) {
  using std::views::iota;
  using std::views::reverse;

  const multimap M(E.begin(), E.end());
  const auto N = order_edge_set(M);

  UnionFind uf(N);
  vector<int> results(E.size());

  // enumerateを使う？ (C++23)
  for (const auto e : iota(0u, E.size()) | reverse) {
    results.at(e) = uf.count_set();
    const auto [u, v] = E.at(e);
    uf.unite(u, v);
  }

  return results;
}


const struct TestParam {
  const Pairs<int> E;
  const vector<int> gold;
} PARAMS[] {
  {
    {
      {0, 1},
      {2, 3},
      {0, 2},
      {1, 2},
      {0, 3},
    },
    {1, 1, 2, 3, 4},
  },
  {
    {
      {1, 2},
      {0, 1},
      {4, 5},
      {2, 3},
      {3, 4},
    },
    {2, 3, 4, 5, 6},
  },
  { {{0, 1}}, {2} },
};

class TestSuite : public testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_THAT(decay(GetParam().E), ElementsAreArray(GetParam().gold));
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    testing::ValuesIn(PARAMS)
                         );
