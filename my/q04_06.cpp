#include "gtest/gtest.h"
#include "type.h"
using std::vector;

// TODO: Use optional
bool func(const int i, const int w, const vector<int> &a, vector<vector<Tri_Bool>> &memo) { // TODO: constexpr (C++20)
  // すでに計算済みならば解をリターン
  if (memo[i][w] != Tri_Undetermined) {
    return memo[i][w];
  }

  // ベースケース
  if (i == 0) {
    if (w == 0) {
      memo[i][w] = Tri_True;
    } else {
      memo[i][w] = Tri_False;
    }
    return memo[i][w];
  }

  // a[i - 1] を選ばない場合, 選ぶ場合
  if (func(i - 1, w, a, memo) || func(i - 1, w - a[i - 1], a, memo)) {
    memo[i][w] = Tri_True;
    return memo[i][w];
  }

  // どちらも false の場合は false
  memo[i][w] = Tri_False;
  return memo[i][w];
}

bool partial_sum_exists(const int w, const vector<int> &a) { // TODO: constexpr  (C++20)
  // 解をメモ化する配列
  vector<vector<Tri_Bool>> memo(a.size() + 1, vector<Tri_Bool>(w + 1, Tri_Undetermined));

  return func(a.size(), w, a, memo);
}

TEST(TestSuite, TestTrue) {
  EXPECT_TRUE(partial_sum_exists(10, {1, 2, 4, 5, 11}));
}

TEST(TestSuite, TestFalse) {
  EXPECT_FALSE(partial_sum_exists(10, {1, 5, 8, 11}));
}
