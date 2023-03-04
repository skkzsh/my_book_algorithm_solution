#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include "template.hpp"
#include <numeric>
using ::testing::TestWithParam;
using ::testing::ValuesIn;
using std::vector;
using std::pair;

// n * p.second = p.first + d
// を満たすような最小の整数 d (>= 0) を返す
int count(const pair<int, int> p) { // TODO: constexpr (C++20)
    int n = 1;
    while (n * p.second < p.first) {
        ++n;
    }
    return n * p.second - p.first;
}

int min_push(Pairs<int> ps) { // TODO: constexpr (C++20)
    vector<int> counts(ps.size());

    for (int i = ps.size() - 1; i >= 0; --i) {
        counts.at(i) = count(ps.at(i));
        // std::cout << "i: "  << i << ", count: " << counts.at(i) << std::endl;  // debug

        for (int j = i; j >= 0; --j) {
            ps.at(j).first += counts.at(i);
        }
    }

    return std::accumulate(counts.begin(), counts.end(), 0); // TODO: using ranges
}


class SubTestSuite : public TestWithParam<SingleTestParam<pair<int, int>>> {};

TEST_P(SubTestSuite, Ex) {
    EXPECT_EQ(count(GetParam().x), GetParam().expected);
}

constexpr SingleTestParam<pair<int, int>> SUB_PARAMS[] {
      {{9, 4}, 3, "a_greater_than_b"},
      {{4, 9}, 5, "a_less_than_b"},
      {{3, 1}, 0, "a_equal_to_multiple_of_b"},
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    SubTestSuite,
    ValuesIn(SUB_PARAMS),
    [](const testing::TestParamInfo<SubTestSuite::ParamType>& info) {
        return (std::string) info.param.test_name;
    }
);


class TestSuite : public TestWithParam<SingleTestParam<Pairs<int>>> {};

TEST_P(TestSuite, Ex) {
    EXPECT_EQ(min_push(GetParam().x), GetParam().expected);
}

const SingleTestParam<Pairs<int>> PARAMS[] {
  {
      {
          {3, 5},
          {2, 7},
          {9, 4},
      },
      7,
  },
  {
      {
          {3, 1},
          {4, 1},
          {5, 9},
          {2, 6},
          {5, 3},
          {5, 8},
          {9, 7},
      },
      22,
  },
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ValuesIn(PARAMS)
);
