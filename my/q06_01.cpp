#include "gmock/gmock.h"
#include <algorithm>
#include <ranges>
using ::testing::ElementsAreArray;
using std::vector;

constexpr vector<int> ranking(const vector<int> &a) {
  using std::ranges::sort;
  using std::ranges::find;
  using std::ranges::to;
  using std::views::transform;

  // aをsortしたvector
  vector sorted(a);
  sort(sorted);

  return a | transform(
                  [sorted](const int i) {
                    return find(sorted, i) - sorted.begin();
                    // find(sorted, a[i]) - sorted.begin();
                    // find(a, sorted[i]) - a.begin();
                  }
                  ) | to<vector<int>>();
}

TEST(TestSuite, Ex) {
  EXPECT_THAT(ranking({12, 43, 7, 15, 9}), ElementsAreArray({2, 4, 0, 3, 1}));
  // sorted: 7, 9, 12, 15, 43
}
