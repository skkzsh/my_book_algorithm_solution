#include "gmock/gmock.h"
#include "gtest-helper.hpp"
#include <ranges>
#include <stack>
using ::testing::ElementsAreArray;
using ::testing::Pair;
using std::string_view;
using std::map;
using std::invalid_argument;

constexpr map<unsigned int, unsigned int> pairing_paren(const string_view parens) {
  // using std::views::enumerate;
  using std::views::iota;

  map<unsigned int, unsigned int> result;
  std::stack<unsigned int> st; // 左括弧の index を格納する stack

  // for (const auto &[i, paren] : parens | enumerate) {
  for (const auto i : iota(0u, parens.length())) {
    switch (parens.at(i)) {
      case '(':
        st.push(i);
        break;
      case ')':
        if (st.empty()) { throw invalid_argument("Missing left paren to pair"); }
        result.insert({st.top(), i});
        st.pop();
        break;
      default:
        throw invalid_argument("Something that isn't paren included");
    }
  }

  if (!st.empty()) { throw invalid_argument("Missing right paren to pair"); }
  return result;
}

// NOTE: mapには右括弧の昇順でinsertされるが, mapのアルゴリズムにより左括弧の昇順に並び替えられている

TEST(TestSuite, Q) {
  EXPECT_THAT(pairing_paren("(()(())())(()())"),
              ElementsAreArray({
                  Pair( 0,  9),
                  Pair( 1,  2),
                  Pair( 3,  6),
                  Pair( 4,  5),
                  Pair( 7,  8),
                  Pair(10, 15),
                  Pair(11, 12),
                  Pair(13, 14),
                })
              );
}

TEST_P(PairStringSuite, Invalid) {
  EXPECT_THROW(pairing_paren(GetParam().first), invalid_argument);
}

constexpr std::pair<string_view, string_view> PARAMS[] {
  {")(", "MissingLeftParen"},
  {"((", "MissingRightParen"},
  {"{}", "NotParens"},
};

INSTANTIATE_TEST_SUITE_P(
  Inst,
  PairStringSuite,
  testing::ValuesIn(PARAMS),
  PrintToSecondParamName
);
