#include "gtest/gtest.h"

// TODO: 実装
int sum(const std::string s) {
    int sum = 0;
    const int l = s.size();

    for (int bit = 0; bit < (1 << (l - 1)); ++bit) {
        for (int i = 0; i < l - 1; ++i) {
            if (bit & (1 << i)) {
                sum += s[i];
            }
        }
    }

    return sum;
}

TEST(TestCase, Test1) {
    // EXPECT_EQ(sum("125"), 176);
}

