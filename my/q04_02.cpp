#include "gtest/gtest.h"
#include <algorithm>
using std::vector;
using std::optional;

long long tribo(const int N, vector<optional<long long>> &memo) {
    if (N < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    // すでに計算済みならば解をリターン
    if (memo[N].has_value()) {
        return memo[N].value();
    }

    // ベースケース
    switch(N) {
        case 0:
        case 1:
            memo[N] = 0; break;
        case 2:
            memo[N] = 1; break;
        default:
            // 答えをメモ化しながら, 再帰呼び出し
            memo[N] = tribo(N - 1, memo) + tribo(N - 2, memo) + tribo(N - 3, memo); break;
    }

    return memo[N].value();
}


vector<long long> tribo_wrapper(const int N) {
    using std::ranges::transform;

    // tribo(N) の解をメモ化する配列
    vector<optional<long long>> memo(N + 1);

    tribo(N, memo);

    // optionalはがし
    vector<long long> result(N + 1); // TODO: views::transformで直接作れないか
    transform(memo, result.begin(),
        [](const optional<auto> x) { return x.value(); } // TODO: ラムダ式やめれないか
    );

    return result;
}

TEST(TestCase, Test10) {
    const vector<long long> result = tribo_wrapper(10);

    EXPECT_EQ(result[10], 81);
    EXPECT_EQ(result[9], 44);
    EXPECT_EQ(result[8], 24);
    EXPECT_EQ(result[7], 13);
    EXPECT_EQ(result[6], 7);
    EXPECT_EQ(result[5], 4);
    EXPECT_EQ(result[4], 2);
    EXPECT_EQ(result[3], 1);
    EXPECT_EQ(result[2], 1);
    EXPECT_EQ(result[1], 0);
    EXPECT_EQ(result[0], 0);
}

TEST(TestCase, Negative) {
    EXPECT_THROW(tribo_wrapper(-1), std::invalid_argument);
}

