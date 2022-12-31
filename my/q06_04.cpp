#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
#include <numeric>

int cows(const std::vector<int> a, const int M) {
    const int N = a.size();

    if (M < 2 || M > N) {
        throw std::invalid_argument("2 <= M <= N required");
    }

    const int M_dash = N;
    std::vector<int> indexes(M_dash);
    std::iota(indexes.begin(), indexes.end(), 0);
    std::vector<int> distances(M_dash - 1);

    for (const int i : std::views::iota(0, M_dash - 1)) {
        distances[i] = a[indexes[i + 1]] - a[indexes[i]];
    }

    return *std::ranges::min_element(distances);
}

//TEST(TestCase, Ex) {
//    EXPECT_EQ(cows({1, 2, 4, 8, 9}, 3), 3);
//}

TEST(TestCase, M_less_than_2) {
    EXPECT_THROW(cows({1, 2, 4, 8, 9}, 1), std::invalid_argument);
}

//TEST(TestCase, M_equal_to_2) {
//    EXPECT_EQ(cows({1, 2, 4, 8, 9}, 2), 8);
//}

TEST(TestCase, M_equal_to_N) {
    EXPECT_EQ(cows({1, 2, 4, 8, 9}, 5), 1);
}

TEST(TestCase, M_greater_than_N) {
    EXPECT_THROW(cows({1, 2, 4, 8, 9}, 6), std::invalid_argument);
}
