#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
#include <ranges>

using std::vector;
using std::ranges::max_element;
using std::ranges::to;
using std::views::filter;
using std::views::transform;
using std::views::cartesian_product;
using std::invalid_argument;

// O(N^4)
constexpr int darts_simple(const vector<int> &a, const int M) {
  // 一時変数をなくしたい
  const vector sums = cartesian_product(a, a, a, a)
                      | transform([](const auto t) { // TODO: 構造化束縛を簡潔に or なくしたい
                          const auto& [p, q, r, s] = t;
                          return p + q + r + s;
                        })
                      | filter([M](const int sum) {
                          return sum <= M;
                        })
                      | to<vector>(); // 直接maxを取りたい

  if (sums.size() == 0) {
    throw invalid_argument("Solution does not exist");
  }

  return *max_element(sums);
}

// O(N^2 log N)
constexpr int darts_binary(const vector<int> &a, const int M) {
  using std::ranges::min_element;
  using std::ranges::sort;
  using std::ranges::upper_bound;
  using std::prev;

  if (4 * *min_element(a) > M) {
    throw invalid_argument("Solution does not exist");
  }

  vector aa = cartesian_product(a, a) | transform([](const auto t) { // TODO: 構造化束縛を簡潔に or なくしたい
                                          const auto& [i, j] = t;
                                          return i + j;
                                        })
                                      | to<vector>();
  sort(aa);

  /*
    問題の言い換え: aaから2つの値aa[i], aa[j]を選んで aa[i] + aa[j] <= M となる最大値を求める
    小問題: aa[j]を固定して、aa[i] <= M - aa[j] となる最大のiを求める
    <=> aa[j]を固定して a[i] > M - a[j] となる最小のiを求める
    aa[i] + aa[j] > M となる最小のi
    <=> aa[i - 1] + aa[j] <= M < aa[i] + aa[j]
  */

  // 一時変数をなくしたい
  const vector tmp = aa | transform([=](const int k) {
                            return k + *prev(upper_bound(aa, M - k));
                          })
                        | to<vector>();  // 直接maxを取りたい

  return *max_element(tmp);
}

// TODO: combine

TEST(TestSuite, Ex1) {
  EXPECT_EQ(darts_simple({3, 14, 15, 9}, 50), 48);
  EXPECT_EQ(darts_binary({3, 14, 15, 9}, 50), 48);
}

TEST(TestSuite, Boundary) {
  EXPECT_EQ(darts_simple({1}, 4), 4);
  EXPECT_EQ(darts_binary({1}, 4), 4);
  // 4を越えない範囲の最大値 <=> 4以下の最大値
  // <=> 4を越えたら例外 (4は例外でない) <=> 5以上は例外
}

TEST(TestSuite, greater_than_M) {
  EXPECT_THROW(darts_simple({1}, 3), invalid_argument);
  EXPECT_THROW(darts_binary({1}, 3), invalid_argument);
  // 3を越えない範囲の最大値 <=> 3以下の最大値
  // <=> 3を越えたら例外 (3は例外でない) <=> 4以上は例外
}
