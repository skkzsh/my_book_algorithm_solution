#include "gtest/gtest.h"
#include "template.hpp"
#include <numeric>
using std::vector;
using std::accumulate;
using std::next;

double aqua(const int M, const vector<int> a) {
    const int N = a.size();

     if (M > N || M < 0) {
         throw std::invalid_argument("0 <= M <= N required");
     }

    vector<vector<double>> dp(N + 1, vector<double>(M + 1, 0));

    // 初期条件
    dp[0][0] = 0;

    for (int n = 1; n <= N; ++n) {
        for (int m = 1; m <= std::min(n, M); ++m) {
            for (int i = 0; i <= n - m; ++i) {
                chmax(dp[n][m], dp[n - i - 1][m - 1] + (double) accumulate(next(a.end(), - N + n - i - 1), next(a.end(), - N + n), 0) / (i + 1));
            }
        }
    }

    // debug
    print2d(dp);

    return dp[N][M];
}

TEST(TestCase, Sample1) {
    const vector<int> a = {9, 1, 2, 3, 9};
    EXPECT_EQ(aqua(3, a), 20);
}

TEST(TestCase, Sample2) {
    const vector<int> a = {14, 4, 9, 7};
    EXPECT_EQ(aqua(1, a), 8.5);
}

TEST(TestCase, Sample3) {
    const vector<int> a = {11, 18, 9, 20, 4, 18, 12, 14};
    EXPECT_EQ(aqua(3, a), 44.7);
}

TEST(TestCase, M_Negative) {
    const vector<int> a = {9, 1, 2, 3, 9};
    EXPECT_THROW(aqua(-1, a), std::invalid_argument);
}
TEST(TestCase, M_GreaterThan_N) {
    const vector<int> a = {9, 1, 2, 3, 9};
    EXPECT_THROW(aqua(6, a), std::invalid_argument);
}
