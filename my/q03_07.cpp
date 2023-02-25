#include "gtest/gtest.h"
#include "gtest-helper.hpp"
using std::string_view;

int sum_bit(string_view S, const int bit) {
    const int L = S.length();
    int sum = 0;
    int tmp = 0;

    for (int i = 0; i < L - 1; ++i) {
        const int num = S[i] - '0';
        if (num < 0 || num > 9) {
            throw std::invalid_argument("argument must be number");
        }

        tmp += num;

        if (bit & (1 << i)) {
            sum += tmp;
            tmp = 0;
        } else {
            tmp *= 10;
        }
    }

    sum += tmp;
    sum += S[L - 1] - '0';
    return sum;
}

int sum_combi(string_view S) {
    const int L = S.size();
    int sum_all = 0;

    for (int bit = 0; bit < (1 << (L - 1)); ++bit) {
        sum_all += sum_bit(S, bit);
    }

    return sum_all;
}


const std::pair<int, int> params[] = {
    {0b00, 125},
    {0b01, 26},
    {0b10, 17},
    {0b11, 8},
};

TEST_P(PairIntSuite, SubTest) {
    EXPECT_EQ(sum_bit("125", GetParam().first), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(
    Inst,
    PairIntSuite,
    ::testing::ValuesIn(params),
    PrintToFirstParamName
);


TEST(TestSuite, Test1) {
    EXPECT_EQ(sum_combi("125"), 176);
}

TEST(TestSuite, NotNumber) {
    EXPECT_THROW(sum_combi("1?5"), std::invalid_argument);
}
