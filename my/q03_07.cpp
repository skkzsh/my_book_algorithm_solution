#include "gtest/gtest.h"

int sum_bit(std::string_view s, const int bit) {
    const int l = s.size();
    int sum = 0;
    int tmp = 0;

    for (int i = 0; i < l - 1; ++i) {
        int num = s[i] - '0';
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
    sum += s[l - 1] - '0';
    return sum;
}

int sum_combi(std::string_view s) {
    const int l = s.size();
    int sum_all = 0;

    for (int bit = 0; bit < (1 << (l - 1)); ++bit) {
        sum_all += sum_bit(s, bit);
    }

    return sum_all;
}

TEST(TestCase, MiniTest00) {
    EXPECT_EQ(sum_bit("125", 0b00), 125);
}

TEST(TestCase, MiniTest01) {
    EXPECT_EQ(sum_bit("125", 0b01), 26);
}

TEST(TestCase, MiniTest10) {
    EXPECT_EQ(sum_bit("125", 0b10), 17);
}

TEST(TestCase, MiniTest11) {
    EXPECT_EQ(sum_bit("125", 0b11), 8);
}

TEST(TestCase, Test1) {
    EXPECT_EQ(sum_combi("125"), 176);
}

TEST(TestCase, IllegalArgumentTest) {
    EXPECT_THROW(sum_combi("1?5"), std::invalid_argument);
}
