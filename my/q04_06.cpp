#include "gtest/gtest.h"
#include "type.h"
using std::vector;

bool func(const int i, const int w, const vector<int> a, vector<vector<Tri_Bool>> &memo) {
    // すでに計算済みならば解をリターン
    if (memo[i][w] != Tri_Undetermined) {
        return memo[i][w];
    }

    // ベースケース
    if (i == 0) {
        if (w == 0) {
            return memo[i][w] = Tri_True;
        } else {
            return memo[i][w] = Tri_False;
        }
    }

    // a[i - 1] を選ばない場合
    if (func(i - 1, w, a, memo)) {
        return memo[i][w] = Tri_True;
    }

    // a[i - 1] を選ぶ場合
    if (func(i - 1, w - a[i - 1], a, memo)) {
        return memo[i][w] = Tri_True;
    }

    // どちらも false の場合は false
    return memo[i][w] = Tri_False;
}

bool partial_sum_exists(const int w, const vector<int> a) {
    // 解をメモ化する配列
    vector<vector<Tri_Bool>> memo(a.size() + 1, vector<Tri_Bool>(w + 1, Tri_Undetermined));

    return func(a.size(), w, a, memo);
}

TEST(TestCase, TestTrue) {
    const vector<int> a = {1, 2, 4, 5, 11};
    EXPECT_EQ(partial_sum_exists(10, a), true);
}

TEST(TestCase, TestFalse) {
    const vector<int> a = {1, 5, 8, 11};
    EXPECT_EQ(partial_sum_exists(10, a), false);
}

