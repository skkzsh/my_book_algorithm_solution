#include "gtest/gtest.h"
#include "template.hpp"
#include <numeric>
using std::vector;

double aqua(const int M, const vector<int> a) {
    const int N = a.size();

     if (M > N || M < 0) {
         throw std::invalid_argument("0 <= M <= N required");
     }

    vector<vector<double>> dp(N + 1, vector<double>(M + 1, -1.0));

    // 初期条件
    dp[0][0] = 0;

    for (int n = 1; n <= N; ++n) {
        for (int m = 1; m <= std::min(n, M); ++m) {
            // (PoC) m = 1の場合
            dp[n][m] = (double) std::accumulate(a.begin(), a.begin() + n, 0) / n;
            // (PoC)
            // 選ぶ場合, 選ばない場合
            if (m == 2) {
                switch (n) {
                    case 2:
                        dp[n][m] = dp[n - 1][m - 1] + a[n - 1];
                        break;
                    case 3:
                        dp[n][m] = std::max({dp[n - 1][m - 1] + a[n - 1],
                                                dp[n - 2][m - 1] + (double) (a[n - 2] + a[n - 1]) / 2,
                                                });
                        break;
                    case 4:
                        dp[n][m] = std::max({dp[n - 1][m - 1] + a[n - 1],
                                                dp[n - 2][m - 1] + (double) (a[n - 2] + a[n - 1]) / 2,
                                                dp[n - 3][m - 1] + (double) (a[n - 3] + a[n - 2] + a[n - 1]) / 3,
                                                });
                        break;
                    case 5:
                        dp[n][m] = std::max({dp[n - 1][m - 1] + a[n - 1],
                                                dp[n - 2][m - 1] + (double) (a[n - 2] + a[n - 1]) / 2,
                                                dp[n - 3][m - 1] + (double) (a[n - 3] + a[n - 2] + a[n - 1]) / 3,
                                                dp[n - 4][m - 1] + (double) (a[n - 4] + a[n - 3] + a[n - 2] + a[n - 1]) / 4,
                                                });
                        break;
                }
            } else if (m == 3) {
                switch (n) {
                    case 3:
                        dp[n][m] = dp[n - 1][m - 1] + a[n - 1];
                        break;
                    case 4:
                        dp[n][m] = std::max({dp[n - 1][m - 1] + a[n - 1],
                                                dp[n - 2][m - 1] + (double) (a[n - 2] + a[n - 1]) / 2,
                                                });
                        break;
                    case 5:
                        dp[n][m] = std::max({dp[n - 1][m - 1] + a[n - 1],
                                                dp[n - 2][m - 1] + (double) (a[n - 2] + a[n - 1]) / 2,
                                                dp[n - 3][m - 1] + (double) (a[n - 3] + a[n - 2] + a[n - 1]) / 3,
                                                });
                        break;
                }
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
