#include "gtest/gtest.h"
#include <algorithm>
#include <unordered_map>

// 3, 5, 7のカウントから算出する
int count753recursive(const int k) {
    if (k < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    if (k < 357) {
        return 0;
    }

    std::unordered_map<int, int> count753map = {
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
                return count753recursive(k - 1);
                break;
        }
    }

    // TODO: 一般化
    // if (count753map[3] > 0 && count753map[5] > 0 && count753map[7] > 0) {
    if (std::all_of(count753map.begin(), count753map.end(),
        [](const auto& x) { return x.second > 0; })) {
        return count753recursive(k - 1) + 1;
    }
    return count753recursive(k - 1);
}

// 3, 5, 7の順列から算出する
int count753permutation(const int k) {
    if (k < 0) {
        throw std::invalid_argument("argument must not be negative");
    }

    std::vector<char> v = {'3', '5', '7'};
    // int digit = std::to_string(k).length(); // TODO: 4ケタ以上の場合に対応する

    std::vector<int> candidates;
    do {
        std::string str(v.begin(), v.end());
        candidates.push_back(std::stoi(str));
    } while (std::next_permutation(v.begin(), v.end()));

    return std::count_if(candidates.begin(), candidates.end(), [k](int c) { return c <= k; });
}


TEST(TestCase, Test0) {
    EXPECT_EQ(count753recursive(356), 0);
    EXPECT_EQ(count753permutation(356), 0);
}

TEST(TestCase, Test1Min) {
    EXPECT_EQ(count753recursive(357), 1);
    EXPECT_EQ(count753permutation(357), 1);
}

TEST(TestCase, Test1Max) {
    EXPECT_EQ(count753recursive(374), 1);
    EXPECT_EQ(count753permutation(374), 1);
}

TEST(TestCase, Test2Min) {
    EXPECT_EQ(count753recursive(375), 2);
    EXPECT_EQ(count753permutation(375), 2);
}

TEST(TestCase, Test4digit1) {
    EXPECT_EQ(count753recursive(1357), 6);
    EXPECT_EQ(count753permutation(1357), 6);
}

TEST(TestCase, Test4digitMin) {
    EXPECT_EQ(count753recursive(3357), 7);
    // EXPECT_EQ(count753permutation(3357), 7); // TODO
}

TEST(TestCase, Negative) {
    EXPECT_THROW(count753recursive(-1), std::invalid_argument);
    EXPECT_THROW(count753permutation(-1), std::invalid_argument);
}

