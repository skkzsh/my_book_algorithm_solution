#include "gtest/gtest.h"
#include <algorithm>
using std::vector;

template<class T> void chmax(T& a, T b) {
    a = std::max(a, b);
}

int happy_max(const int N, const vector<vector<int>> z) {
    vector<vector<int>> dp(N + 1, vector<int>(3, 0));

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < 3; ++j) {
            for(int k = 0; k < 3; ++k) {
                if (j == k) {
                    continue;
                }
                chmax(dp[i + 1][j], dp[i][k] + z[i][j]);
            }
        }
        // 2日連続で同じ行動してもいい場合
        // dp[i + 1] = dp[i] + std::max({a[i], b[i], c[i]});
    }

    return *std::max_element(dp[N].begin(), dp[N].end());
}


TEST(TestCase, Test0) {
    const vector<vector<int>> z = {};

    EXPECT_EQ(happy_max(0, z), 0);
}

TEST(TestCase, Test1) {
    const vector<vector<int>> z = {
        vector<int>{1, 3, 2},
    };

    EXPECT_EQ(happy_max(1, z), 3);
}

TEST(TestCase, Test2) {
    const vector<vector<int>> z = {
        vector<int>{100, 10, 1},
        vector<int>{110, 11, 2},
    };

    EXPECT_EQ(happy_max(2, z), 120);
}

TEST(TestCase, Example1) {
    const vector<vector<int>> z = {
        vector<int>{10, 40, 70},
        vector<int>{20, 50, 80},
        vector<int>{30, 60, 90},
    };

    EXPECT_EQ(happy_max(3, z), 210);
}

TEST(TestCase, Example3) {
    const vector<vector<int>> z = {
        vector<int>{6, 7, 8},
        vector<int>{8, 8, 3},
        vector<int>{2, 5, 2},
        vector<int>{7, 8, 6},
        vector<int>{4, 6, 8},
        vector<int>{2, 3, 4},
        vector<int>{7, 5, 1},
    };

    EXPECT_EQ(happy_max(7, z), 46);
}

