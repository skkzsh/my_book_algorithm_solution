#include "gtest/gtest.h"
#include "template.hpp"
#include <algorithm>
using std::string;
using std::string_view;
using std::get;

constexpr string longest_common_substring(const string_view S, const string_view T) {
  using std::vector;
  using namespace std::ranges;
  vector<vector<string>> dp(S.length() + 1, vector<string>(T.length() + 1));

  // もらう方式
  for (size_t i = 1; i <= S.length(); ++i) {
    for (size_t j = 1; j <= T.length(); ++j) {
      if (S[i - 1] == T[j - 1]) { // i字目 = j文字目を選ぶ場合
        dp[i][j] = dp[i - 1][j - 1] + S[i - 1];
      } else { // i字目を選ばない場合, j字目を選ばない場合
        dp[i][j] = max({dp[i - 1][j], dp[i][j - 1]}, {}, size);
      }
    }
  }

  // debug
  print2d(dp);

  return dp[S.length()][T.length()];
}


class TestSuite : public ::testing::TestWithParam<std::tuple<string_view, string_view, string_view>> {};

TEST_P(TestSuite, Ex) {
  const auto [S, T, gold] = GetParam();
  EXPECT_EQ(longest_common_substring(S, T), gold);
}

constexpr std::tuple<string_view, string_view, string_view> PARAMS[] {
  {"axyb", "abyxb", "axb"}, // aybでも可
  {"aa", "xayaz", "aa"},
  {"a", "z", ""},
  {"abracadabra", "avadakedavra", "aaadara"},
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    TestSuite,
    ::testing::ValuesIn(PARAMS)
                         );
