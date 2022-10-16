#include "gtest/gtest.h"

int count_simple(int k, int n) {
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

int count_better(int k, int n) {
    if (3 * k < n) { // この場合, 条件を満たす組は存在しない
        return 0;
    }

    // k > nの場合, 0 <= x,y,z <= nの範囲のみ探索すれば十分
    int boundary = std::min(k, n);

    int count = 0;
    for (int x = 0; x <= boundary; x++) {
        for (int y = 0; y <= boundary; y++) {
            int z = n - x - y;
            if (z >= 0 && z <= k) {
                count++;
            }
        }
    }
    return count;
}

TEST(TestCase, NotExist) {
    EXPECT_EQ(0, count_simple(3, 10));
    EXPECT_EQ(0, count_better(3, 10));
}

TEST(TestCase, Test1) {
    EXPECT_EQ(10, count_simple(3, 3));
    EXPECT_EQ(10, count_better(3, 3));
}

TEST(TestCase, Test2) {
    EXPECT_EQ(10, count_simple(10, 3));
    EXPECT_EQ(10, count_better(10, 3));
}
