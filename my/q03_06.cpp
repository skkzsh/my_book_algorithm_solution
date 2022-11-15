#include "gtest/gtest.h"

int count_simple(const int k, const int n) {
    int count = 0;
    for (int x = 0; x <= k; x++) {
        for (int y = 0; y <= k; y++) {
            if (int z = n - x - y; z >= 0 && z <= k) {
                count++;
            }
        }
    }
    return count;
}

int count_better(const int k, const int n) {
    if (k < 0 || n < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    if (3 * k < n) { // この場合, 条件を満たす組は存在しない
        return 0;
    }

    // k > nの場合, 0 <= x,y,z <= nの範囲のみ探索すれば十分
    const int boundary = std::min(k, n);

    int count = 0;
    for (int x = 0; x <= boundary; x++) {
        for (int y = 0; y <= boundary; y++) {
            if (int z = n - x - y; z >= 0 && z <= k) {
                count++;
            }
        }
    }
    return count;
}

TEST(TestCase, SolutionNotExists) {
    EXPECT_EQ(count_simple(3, 10), 0);
    EXPECT_EQ(count_better(3, 10), 0);
}

TEST(TestCase, k_equal_to_n) {
    EXPECT_EQ(count_simple(3, 3), 10);
    EXPECT_EQ(count_better(3, 3), 10);
}

TEST(TestCase, k_greater_than_n) {
    EXPECT_EQ(count_simple(10, 3), 10);
    EXPECT_EQ(count_better(10, 3), 10);
}

TEST(TestCase, k_negative) {
    EXPECT_THROW(count_better(-1, 3), std::invalid_argument);
}

TEST(TestCase, n_negative) {
    EXPECT_THROW(count_better(3, -1), std::invalid_argument);
}
