#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <algorithm>
using ::testing::ElementsAreArray;
using std::vector;
using std::optional;

long long tribo(const int N, vector<optional<long long>> &memo) {
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
    if (N < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    using std::ranges::transform;

    // tribo(N) の解をメモ化する配列
    vector<optional<long long>> memo(N + 1);

    tribo(N, memo);

    // optionalはがし
    vector<long long> results(N + 1); // TODO: views::transformで直接作れないか
    transform(memo, results.begin(),
        [](const optional<auto> x) { return x.value(); } // TODO: ラムダ式やめれないか
    );

    return results;
}

TEST(TestCase, Test10) {
    EXPECT_THAT(tribo_wrapper(10), ElementsAreArray({0, 0, 1, 1, 2, 4, 7, 13, 24, 44, 81}));
}

TEST(TestCase, Negative) {
    EXPECT_THROW(tribo_wrapper(-1), std::invalid_argument);
}

