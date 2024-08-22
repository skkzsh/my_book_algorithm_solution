#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
using std::vector;
using std::invalid_argument;

// O(N^4)
consteval int darts_simple(const vector<int> &a, const int M) {
  int max = -1;

  // TODO: cartesian_product (C++23)
  for (const int p : a) {
    for (const int q : a) {
      for (const int r : a) {
        for (const int s : a) {
          if (const int tmp = p + q + r + s; tmp <= M) {
            chmax(max, tmp);
          }
        }
      }
    }
  }

  return max;
}

// O(N^2 log N)
constexpr int darts_binary(const vector<int> &a, const int M) {
  using namespace std::ranges;
  using std::prev;

  if (4 * *min_element(a) > M) {
    throw invalid_argument("Solution does not exist");
  }

  // TODO: cartesian_product (C++23)
  vector<int> aa(a.size() * a.size());
  for (const int i : a) {
    for (const int j : a) {
      aa.push_back(i + j);
    }
  }
  sort(aa);

  /*
    問題の言い換え: aaから2つの値aa[i], aa[j]を選んで aa[i] + aa[j] <= M となる最大値を求める
    小問題: aa[j]を固定して、aa[i] <= M - aa[j] となる最大のiを求める
    <=> aa[j]を固定して a[i] > M - a[j] となる最小のiを求める
    aa[i] + aa[j] > M となる最小のi
    <=> aa[i - 1] + aa[j] <= M < aa[i] + aa[j]
  */

  vector<int> tmp(aa.size());
  for (const int k : aa) {
    tmp.push_back(k + *prev(upper_bound(aa, M - k)));
  }

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
  EXPECT_EQ(darts_simple({1}, 3), -1);
  EXPECT_THROW(darts_binary({1}, 3), invalid_argument);
  // 3を越えない範囲の最大値 <=> 3以下の最大値
  // <=> 3を越えたら例外 (3は例外でない) <=> 4以上は例外
}
