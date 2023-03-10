#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include "template.hpp"
#include <algorithm>

constexpr int max_pairing(Pairs<int> r, Pairs<int> b) {
  constexpr int INF = 1 << 29; // 十分大きな値

  using std::ranges::sort;
  sort(r);
  sort(b);

  std::vector<bool> used(r.size());  // rが使用済かどうか
  int count = 0;

  // TODO: using iota
  for (size_t j = 0; j < b.size(); j++) {
    int max_second = - INF;
    std::optional<int> max_key;

    for (size_t i = 0; i < r.size(); i++) {
      if (!used.at(i) && r.at(i).first < b.at(j).first && r.at(i).second < b.at(j).second) {
        if (max_second < r.at(i).second) {
          max_second = r.at(i).second;
          max_key = i;
        }
      }
    }

    if (max_key.has_value()) {
      ++count;
      used.at(max_key.value()) = true;
    }
  }

  return count;
}


class TestSuite : public ::testing::TestWithParam<PairTestParam<Pairs<int>>> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(max_pairing(GetParam().a, GetParam().b), GetParam().expected);
}

const PairTestParam<Pairs<int>> PARAMS[] {
  {
    {
      {2, 0},
      {3, 1},
      {1, 3},
    },
    {
      {4, 2},
      {0, 4},
      {5, 5},
    },
    2,
  },
  {
    {
      {0, 0},
      {1, 1},
      {5, 2},
    },
    {
      {2, 3},
      {3, 4},
      {4, 5},
    },
    2,
  },
  {
    {
      {2, 2},
      {3, 3},
    },
    {
      {0, 0},
      {1, 1},
    },
    0,
  },
  {
    {
      {0, 0},
      {7, 3},
      {2, 2},
      {4, 8},
      {1, 6},
    },
    {
      {8, 5},
      {6, 9},
      {5, 4},
      {9, 1},
      {3, 7},
    },
    5,
  },
  {
    {
      {0, 0},
      {1, 1},
      {5, 5},
      {6, 6},
      {7, 7},
    },
    {
      {2, 2},
      {3, 3},
      {4, 4},
      {8, 8},
      {9, 9},
    },
    4,
  },
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
