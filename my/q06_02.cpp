#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include <algorithm>
#include <ranges>

using std::vector;
using std::tuple;
using std::get;

template<class T> using Trio = tuple<vector<T>, vector<T>, vector<T>>;

// O(N ^ 3)
constexpr unsigned int festival_simple(const Trio<int> &z) {
  unsigned int count = 0;

  for (const int a : get<0>(z)) {
    for (const int b : get<1>(z)) {
      if (a < b) {
        for (const int c : get<2>(z)) {
          if (b < c) {
            ++count;
          }
        }
        // count += std::ranges::count_if(z[2], [b](int c){ return b < c; });
      }
    }
  }

  return count;
}

// O(N log N)
constexpr unsigned int festival_binary(Trio<int> z) {
  using namespace std::ranges;

  // for (const int i : std::views::iota(0, 3)) {
  //   sort(get<i>(z));
  // }

  sort(get<0>(z));
  sort(get<1>(z));
  sort(get<2>(z));

  unsigned int count = 0;

  for (const int b : get<1>(z)) {
    count += (lower_bound(get<0>(z), b) - get<0>(z).begin()) // a[i] >= b となる最小のi <=> a[i - 1] < b <= a[i] => 数は (i - 1) - 0 + 1 = iコ
             * (get<2>(z).end() - upper_bound(get<2>(z), b)); // c[i] > b となる最小のi => 数は N - i + 1 => c.end() - i
    // count += (lower_bound(get<0>(z), b) - get<0>(z).begin())
    //             * (N - (upper_bound(get<2>(z), b) - get<2>(z).begin()));
  }

  return count;
}


class TestSuite : public ::testing::TestWithParam<SingleTestParam<Trio<int>>> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(festival_simple(GetParam().x), GetParam().expected);
  EXPECT_EQ(festival_binary(GetParam().x), GetParam().expected);
}

const SingleTestParam<Trio<int>> PARAMS[] {
  {
    {
      {1, 5},
      {2, 4},
      {3, 6},
    },
    3,
  },
  {
    {
      {1, 1, 1},
      {2, 2, 2},
      {3, 3, 3},
    },
    27,
  },
  {
    {
      {3, 14, 159, 2, 6, 53},
      {58, 9, 79, 323, 84, 6},
      {2643, 383, 2, 79, 50, 288},
    },
    87,
  },
  {
    {
      {1, 1},
      {1, 1},
      {2, 2},
    },
    0,
  },
  {
    {
      {1, 1},
      {2, 2},
      {2, 2},
    },
    0,
  },
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
