#include "gtest/gtest.h"
using std::string;

template<class T> void print2d(vector<vector<T>> vv) {
    std::cout << "print2d start" << std::endl;
    for (vector<T> v : vv) {
        for (T i : v) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "print2d end" << std::endl;
}

string longest_common_substring(const string S, const string T) {
    using std::vector;
    vector<vector<string>> dp(S.length() + 1, vector<string>(T.length() + 1, ""));

    // もらう方式
    for (size_t i = 1; i <= S.length(); ++i) {
        for (size_t j = 1; j <= T.length(); ++j) {
            if (S[i - 1] == T[j - 1]) { // i字目 = j文字目を選ぶ場合
                dp[i][j] = dp[i - 1][j - 1] + S[i - 1];
            } else { // i字目を選ばない場合, j字目を選ばない場合
                // TODO: max()を使えないか
                dp[i][j] = dp[i - 1][j].length() > dp[i][j - 1].length() ? dp[i - 1][j] : dp[i][j - 1];
            }
         }
     }

    // debug
    print2d(dp);

    return dp[S.length()][T.length()];
}


TEST(TestCase, Ex1) {
    EXPECT_EQ(longest_common_substring("axyb", "abyxb"), "ayb"); // axbでも可
}

TEST(TestCase, Ex2) {
    EXPECT_EQ(longest_common_substring("aa", "xayaz"), "aa");
}

TEST(TestCase, Ex3) {
    EXPECT_EQ(longest_common_substring("a", "z"), "");
}

TEST(TestCase, Ex4) {
    EXPECT_EQ(longest_common_substring("abracadabra", "avadakedavra"), "aaadara");
}
