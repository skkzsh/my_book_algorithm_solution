#include "gmock/gmock.h"
using ::testing::ElementsAreArray;
using ::testing::Pair;
using std::map;
using std::set;
using std::pair;

// E: 辺集合 (重み付き, 無向グラフ)
constexpr set<pair<int, int>> kruskal(const map<pair<int, int>, int> &E) {
  // TODO: 実装
  return {};
}

TEST(TestSuite, Ex) {
  const map<pair<int, int>, int> E {
      {{0, 3},  5},
      {{0, 5},  6},
      {{0, 7},  3},
      {{1, 4},  4},
      {{1, 6},  3},
      {{2, 4},  9},
      {{2, 5}, 10},
      {{2, 7},  5},
      {{3, 7},  6},
      {{4, 6},  2},
      {{6, 7},  7},
  };

  EXPECT_THAT(kruskal(E), ElementsAreArray({
    Pair(0, 3),
    Pair(0, 5),
    Pair(0, 7),
    Pair(1, 6),
    Pair(2, 7),
    Pair(4, 6),
    Pair(6, 7),
  }));
}
