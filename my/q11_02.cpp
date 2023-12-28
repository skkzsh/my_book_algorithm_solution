#include "gmock/gmock.h"
#include "union-find.hpp"
#include "template.hpp"
using ::testing::ElementsAreArray;
using std::vector;

// E: 辺集合 (0以上の連番であること)
// N: 頂点数 (Gと整合が取れていること)
vector<int> decay(const Pairs<int> &E, const int N) {
  // const int N = ;  // TODO
  UnionFind uf(N);
  vector<int> results(E.size());

  for (int e = E.size() - 1; e >= 0; --e) {
    results.at(e) = uf.count_set();
    uf.unite(E.at(e).first, E.at(e).second);
  }

  return results;
}


const struct TestParam {
  const Pairs<int> E;
  const int N;
  const vector<int> expected;
} PARAMS[] {
  {
    {
      {0, 1},
      {2, 3},
      {0, 2},
      {1, 2},
      {0, 3},
    },
    4,
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
    6,
    {2, 3, 4, 5, 6},
  },
  { {{0, 1}}, 2, {2} },
};

class TestSuite : public ::testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_THAT(decay(GetParam().E, GetParam().N), ElementsAreArray(GetParam().expected));
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
