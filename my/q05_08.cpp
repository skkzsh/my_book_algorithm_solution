#include "gtest/gtest.h"
#include "template.hpp"
#include <numeric>
#include <algorithm>
// #include <ranges>
using std::vector;

double aqua(const int M, const vector<int> a) {
    using std::accumulate;
    using std::next;
    using namespace std::ranges;
    constexpr int INF = 1 << 29; // 十分大きな値

    const int N = a.size();

     if (M > N || M < 0) {
         throw std::invalid_argument("0 <= M <= N required");
     }

    vector<vector<double>> dp(N + 1, vector<double>(M + 1, - INF));

    // 初期条件
    dp[0][0] = 0;

    // もらう方式
    for (int n = 1; n <= N; ++n) {
        for (int m = 1; m <= min(n, M); ++m) {
            // TODO: 一時変数なくせないか
            // auto tmp = std::views::iota(0, n - m + 1) | std::views::transform([=](const int i) {
            //      return dp[n - i - 1][m - 1] + (double) accumulate(next(a.end(), - N + n - i - 1), next(a.end(), - N + n), 0) / (i + 1);
            // });
            vector<double> tmp(n - m + 1);
            for (int i = 0; i <= n - m; ++i) {
                tmp[i] = dp[n - i - 1][m - 1] + (double) accumulate(next(a.end(), - N + n - i - 1), next(a.end(), - N + n), 0) / (i + 1);
            }
            dp[n][m] = *max_element(tmp);
        }
    }

    // debug
    print2d(dp);

    return dp[N][M];
}

TEST(TestSuite, Sample1) {
    const vector<int> a {9, 1, 2, 3, 9};
    EXPECT_EQ(aqua(3, a), 20);
}

TEST(TestSuite, Sample2) {
    const vector<int> a {14, 4, 9, 7};
    EXPECT_EQ(aqua(1, a), 8.5);
}

TEST(TestSuite, Sample3) {
    const vector<int> a {11, 18, 9, 20, 4, 18, 12, 14};
    EXPECT_DOUBLE_EQ(aqua(3, a), 44.66666666666667);
}

TEST(TestSuite, M_Negative) {
    const vector<int> a {9, 1, 2, 3, 9};
    EXPECT_THROW(aqua(-1, a), std::invalid_argument);
}
TEST(TestSuite, M_GreaterThan_N) {
    const vector<int> a {9, 1, 2, 3, 9};
    EXPECT_THROW(aqua(6, a), std::invalid_argument);
}
