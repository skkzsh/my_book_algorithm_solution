#include "gtest/gtest.h"

int count753(const int k) {
    if (k < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    if (k < 357) {
        return 0;
    }

    std::map<int, int> count753map = {
        {3, 0},
        {5, 0},
        {7, 0},
    };

    for (int tail = k; tail > 0; tail /= 10) {
        switch(tail % 10) {
            case 3:
            case 5:
            case 7:
                count753map[tail % 10]++;
                break;
            default:
                return count753(k - 1);
                break;
        }
    }

    // if (std::all_of(count753map.begin(), count753map.end(),
    //             [](std::map<int, int>::iterator x) { return (x -> second > 0); })) {
    if (count753map[3] > 0 && count753map[5] > 0 && count753map[7] > 0) {
        return count753(k - 1) + 1;
    }
    return count753(k - 1);
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

TEST(TestCase, Test4digit1) {
    EXPECT_EQ(count753(1357), 6);
}

TEST(TestCase, Test4digitMin) {
    EXPECT_EQ(count753(3357), 7);
}

TEST(TestCase, Negative) {
    EXPECT_THROW(count753(-1), std::invalid_argument);
}

