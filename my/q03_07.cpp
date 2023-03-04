#include "gtest/gtest.h"
using std::string_view;
using std::invalid_argument;

constexpr int sum_bit(string_view S, const int bit) {
    const int L = S.length();
    int sum = 0;
    int tmp = 0;

    for (int i = 0; i < L - 1; ++i) {
        const int num = S.at(i) - '0';
        if (num < 0 || num > 9) {
            throw invalid_argument("argument must be number");
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
    sum += S.at(L - 1) - '0';
    return sum;
}

constexpr int sum_combi(string_view S) {
    const int L = S.size();
    int sum_all = 0;

    for (int bit = 0; bit < (1 << (L - 1)); ++bit) {
        sum_all += sum_bit(S, bit);
    }

    return sum_all;
}


class SubTestSuite : public ::testing::TestWithParam<std::pair<int, int>> {};

TEST_P(SubTestSuite, Test) {
    EXPECT_EQ(sum_bit("125", GetParam().first), GetParam().second);
}

constexpr std::pair<int, int> PARAMS[] {
    {0b00, 125},
    {0b01, 26},
    {0b10, 17},
    {0b11, 8},
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    SubTestSuite,
    ::testing::ValuesIn(PARAMS),
    [](const testing::TestParamInfo<SubTestSuite::ParamType>& info) {
        return std::to_string(info.param.first);
    }
);


TEST(TestSuite, Test1) {
    EXPECT_EQ(sum_combi("125"), 176);
}

TEST(TestSuite, NotNumber) {
    EXPECT_THROW(sum_combi("1?5"), invalid_argument);
}
