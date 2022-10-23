#include "gtest/gtest.h"

bool func(const int i, const int w, const std::vector<int> a) {
    // ベースケース
    if (i == 0) {
        if (w == 0) {
            return true;
        } else {
            return false;
        }
    }

    // a[i - 1] を選ばない場合
    if (func(i - 1, w, a)) {
        return true;
    }

    // a[i - 1] を選ぶ場合
    if (func(i - 1, w - a[i - 1], a)) {
        return true;
    }

    // どちらも false の場合は false
    return false;
}

bool partial_sum_exists(const int w, const std::vector<int> a) {
    return func(a.size(), w, a);
}

TEST(TestCase, TestTrue) {
    const std::vector<int> a = {1, 2, 4, 5, 11};
    EXPECT_EQ(partial_sum_exists(10, a), true);
}

TEST(TestCase, TestFalse) {
    const std::vector<int> a = {1, 5, 8, 11};
    EXPECT_EQ(partial_sum_exists(10, a), false);
}

