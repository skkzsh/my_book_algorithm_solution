#include "gtest/gtest.h"

int count(int k, int n) {
    int count = 0;
    for (int x = 0; x <= k; x++) {
        for (int y = 0; y <= k; y++) {
            int z = n - x - y;
            if (z >= 0 && z <= k) {
                count++;
            }
        }
    }
    return count;
}

TEST(TestCase, NotExist) {
    EXPECT_EQ(0, count(3, 10));
}

TEST(TestCase, Test1) {
    EXPECT_EQ(10, count(3, 3));
}

TEST(TestCase, Test2) {
    EXPECT_EQ(10, count(10, 3));
}
