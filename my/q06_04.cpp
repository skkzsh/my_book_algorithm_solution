#include "gtest/gtest.h"
#include <ranges>

int cows(const std::vector<int> a, const int M) {
    const int N = a.size();

    if (M < 2 || M > N) {
        throw std::invalid_argument("2 <= M <= N required");
    }

    // 元の問題: 「選んだMコの小屋のうち2つの小屋の距離の最小値」の最大値を求める
    // <=> 判定問題: 「選んだMコの小屋のうち2つの小屋の距離の最小値」をx以上にすることができるか
    // <=> 判定問題: 選んだMコの小屋のすべての距離をx以上にすることができるか
    // <=> 判定問題: すべての小屋の距離をx以上にして, 小屋をMコを選べるか

    int left = 0; // 常にtrue
    int right = a[N - 1] + 1; // 常にfalse

    while (right - left > 1) {
        const int x = (left + right) / 2;

        int prev = 0; // 前回選んだ小屋のindex
        int count = 1; // 小屋を選んだ個数

        // 貪欲法
        for (const int i : std::views::iota(0, N)) {
            if (a[i] - a[prev] >= x) {
                count++;
                prev = i;
            };
        }

        if (count >= M) { // Mコ以上選べた => もっと距離を離せる => xはもっと大きい (true領域を更新)
            left = x;
        } else {  // Mコ選べなかった => 距離を離せていない => xはもっと小さい (false領域を更新)
            right = x;
        }
    }

    return left;
}

TEST(TestCase, Ex) {
    EXPECT_EQ(cows({1, 2, 4, 8, 9}, 3), 3);
}

TEST(TestCase, M_less_than_2) {
    EXPECT_THROW(cows({1, 2, 4, 8, 9}, 1), std::invalid_argument);
}

TEST(TestCase, M_equal_to_2) {
    EXPECT_EQ(cows({1, 2, 4, 8, 9}, 2), 8);
}

TEST(TestCase, M_equal_to_N) {
    EXPECT_EQ(cows({1, 2, 4, 8, 9}, 5), 1);
}

TEST(TestCase, M_greater_than_N) {
    EXPECT_THROW(cows({1, 2, 4, 8, 9}, 6), std::invalid_argument);
}
