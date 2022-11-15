#include "gtest/gtest.h"
#include "template.hpp"
using std::string;

string longest_common_substring(const string S, const string T) {
    using std::vector;
    vector<vector<string>> dp(S.length() + 1, vector<string>(T.length() + 1, ""));

    // もらう方式
    for (size_t i = 1; i <= S.length(); ++i) {
        for (size_t j = 1; j <= T.length(); ++j) {
            if (S[i - 1] == T[j - 1]) { // i字目 = j文字目を選ぶ場合
                dp[i][j] = dp[i - 1][j - 1] + S[i - 1];
            } else { // i字目を選ばない場合, j字目を選ばない場合
                dp[i][j] = std::max({dp[i - 1][j], dp[i][j - 1]}, [](auto a, auto b) { return a.length() < b.length(); });
            }
         }
     }

    // debug
    print2d(dp);

    return dp[S.length()][T.length()];
}


TEST(TestCase, Ex1) {
    EXPECT_EQ(longest_common_substring("axyb", "abyxb"), "axb"); // aybでも可
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
