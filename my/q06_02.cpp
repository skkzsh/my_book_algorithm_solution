#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include <algorithm>
#include <ranges>

using std::vector;
using std::tuple;
using std::get;

template<class T> using Trio = tuple<vector<T>, vector<T>, vector<T>>;

// O(N ^ 3)
constexpr unsigned int festival_simple(const Trio<int> &Z) {
  unsigned int count = 0;

  const auto [A, B, C] = Z;

  for (const int a : A) {
    for (const int b : B) {
      if (a < b) {
        for (const int c : C) {
          if (b < c) {
            ++count;
          }
        }
        // count += std::ranges::count_if(Z[2], [b](int c){ return b < c; });
      }
    }
  }

  return count;
}

// O(N log N)
constexpr unsigned int festival_binary(Trio<int> Z) {
  using namespace std::ranges;

  // for (const int i : std::views::iota(0, 3)) {
  //   sort(get<i>(Z));
  // }

  auto [A, B, C] = Z;

  sort(A);
  sort(B);
  sort(C);

  unsigned int count = 0;

  for (const int b : B) {
    count += (lower_bound(A, b) - A.begin()) // a[i] >= b となる最小のi <=> a[i - 1] < b <= a[i] => 数は (i - 1) - 0 + 1 = iコ
             * (C.end() - upper_bound(C, b)); // c[i] > b となる最小のi => 数は N - i + 1 => c.end() - i
    // count += (lower_bound(A, b) - A.begin())
    //             * (N - (upper_bound(C, b) - C.begin()));
  }

  return count;
}


const struct TestParam {
  const Trio<int> Z;
  const unsigned int gold;
} PARAMS[] {
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

class TestSuite : public ::testing::TestWithParam<TestParam> {};

TEST_P(TestSuite, Ex) {
  EXPECT_EQ(festival_simple(GetParam().Z), GetParam().gold);
  EXPECT_EQ(festival_binary(GetParam().Z), GetParam().gold);
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
