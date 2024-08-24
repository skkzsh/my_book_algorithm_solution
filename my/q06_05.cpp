#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
using std::vector;
using std::invalid_argument;
using std::ranges::sort;

// O(N^2 * log N)
consteval int product_th_simple(const vector<int> &a, const vector<int> &b, const int K) {
   using std::views::cartesian_product;
   using std::views::transform;
   using std::ranges::to;

   // TODO: 構造化束縛を簡潔に or なくしたい
   vector p = cartesian_product(a, b) | transform([](const auto t) {
                                          const auto& [i, j] = t;
                                          return i * j;
                                        })
                                      | to<vector>();

  sort(p);

  return p.at(K - 1);
}

/*
  元の問題: a[i] * b[j] の中でK番目に小さい値をを求める
  <=> 判定問題: a[i] * b[j] のうちx以下がKコ (以上) あるかどうか
*/

// a[i] * b[j] <= x の数を返す関数
// a, bはソート済が前提
// O(N * log N)
constexpr int countx(const vector<int> &a, const vector<int> &b, const int x) {
  /*
    a[i] を固定して b[j] <= x / a[i] となる最大のjを求める
    <=> a[i] を固定して b[j] > x / a[i] となる最小のjを求める
    <=> b[j - 1] <= x / a[i] < b[j]

    j - 1 までで (j - 1) - 0 + 1 = jコ
  */
  using std::ranges::upper_bound;

  int count = 0;
  for (const int m : a) {
    count += upper_bound(b, x / m) - b.begin();
  }
  return count;
}

// O(N * log N * log C)
constexpr int product_th_binary(vector<int> a, vector<int> b, const int K) {
  sort(a);
  sort(b);

  if (a.at(0) <= 0 || b.at(0) <= 0) {
    throw invalid_argument("a and b must be positive numbers");
  }

  int left = 0; // 常にfalse (∵ a, b > 0)
  int right = a.at(a.size() - 1) * b.at(b.size() - 1); // 常にtrue

  while (right - left > 1) {
    if (const int x = (left + right) / 2; countx(a, b, x) >= K) {
      right = x;
    } else {
      left = x;
    }
  }

  return right;
}

// TODO: combine

TEST(TestSuite, Ex1) {
  EXPECT_EQ(product_th_simple({2, 3}, {3, 5}, 3), 10);
  EXPECT_EQ(product_th_binary({2, 3}, {3, 5}, 3), 10);
}

TEST(TestSuite, Ex2) {
  EXPECT_EQ(product_th_simple({1, 2, 1}, {2, 1, 2}, 7), 2);
  EXPECT_EQ(product_th_binary({1, 2, 1}, {2, 1, 2}, 7), 2);
}

TEST(TestSuite, Zero) {
  EXPECT_THROW(product_th_binary({1, 0, 1}, {1, 1, 1}, 1), invalid_argument);
  EXPECT_THROW(product_th_binary({1, 1, 1}, {1, 1, 0}, 1), invalid_argument);
}
