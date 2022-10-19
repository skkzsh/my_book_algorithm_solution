#include "gtest/gtest.h"

int count753(int k) {
    if (k < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    return k;
}


TEST(TestCase, Test0) {
    EXPECT_EQ(count753(356), 0);
}

TEST(TestCase, Test1Min) {
    EXPECT_EQ(count753(357), 1);
}

TEST(TestCase, Test1Max) {
    EXPECT_EQ(count753(374), 1);
}

TEST(TestCase, Test2Min) {
    EXPECT_EQ(count753(375), 2);
}

TEST(TestCase, Negative) {
    EXPECT_THROW(count753(-1), std::invalid_argument);
}

