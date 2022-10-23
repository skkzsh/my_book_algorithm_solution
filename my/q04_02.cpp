#include "gtest/gtest.h"

//  FIXME: 参照渡しをやめたい
int tribo(const int N, std::vector<long long> &memo) {
    if (N < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    // ベースケース
    switch(N) {
        case 0:
        case 1:
            return memo[N] = 0;
        case 2:
            return memo[N] = 1;
        default:
            break;
    }

    // すでに計算済みならば解をリターン
    if (memo[N] != -1) {
        return memo[N];
    }

    // 答えをメモ化しながら, 再帰呼び出し
    return memo[N] = tribo(N - 1, memo) + tribo(N - 2, memo) + tribo(N - 3, memo);
}


std::vector<long long> tribo_wrapper(const int N) {
    // tribo(N) の解をメモ化する配列
    std::vector<long long> memo(N + 1, -1);

    tribo(N, memo);

    return memo;
}

TEST(TestCase, Test10) {
    std::vector<long long> memo = tribo_wrapper(10);

    EXPECT_EQ(memo[10], 81);
    EXPECT_EQ(memo[9], 44);
    EXPECT_EQ(memo[8], 24);
    EXPECT_EQ(memo[7], 13);
    EXPECT_EQ(memo[6], 7);
    EXPECT_EQ(memo[5], 4);
    EXPECT_EQ(memo[4], 2);
    EXPECT_EQ(memo[3], 1);
    EXPECT_EQ(memo[2], 1);
    EXPECT_EQ(memo[1], 0);
    EXPECT_EQ(memo[0], 0);
}

TEST(TestCase, Negative) {
    EXPECT_THROW(tribo_wrapper(-1), std::invalid_argument);
}

