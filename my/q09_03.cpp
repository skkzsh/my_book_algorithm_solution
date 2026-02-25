#include "gmock/gmock.h"
#include <ranges>
#include <algorithm>
#include <stack>
#include <expected>
using std::expected;
using std::unexpected;
using std::map;
using std::string_view;
using std::string;
using ::testing::ElementsAreArray;
using ::testing::Pair;

constexpr expected<map<unsigned int, unsigned int>, string> pairing_paren(const string_view parens) {
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
        if (st.empty()) { return unexpected("Missing left paren to pair"); }
        result.insert({st.top(), i});
        st.pop();
        break;
      default:
        return unexpected("Something that isn't paren included");
    }
  }

  if (!st.empty()) { return unexpected("Missing right paren to pair"); }
  return result;
}

// NOTE: mapには右括弧の昇順でinsertされるが, mapのアルゴリズムにより左括弧の昇順に並び替えられている

TEST(TestSuite, Q) {
  EXPECT_THAT(pairing_paren("(()(())())(()())").value(),
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


constexpr struct UnexpectedTestParam {
  const string_view parens;
  const string_view message;
} PARAMS[] {
  {")(", "Missing left paren to pair"},
  {"((", "Missing right paren to pair"},
  {"{}", "Something that isn't paren included"},
};

class UnexpectedTestSuite : public testing::TestWithParam<UnexpectedTestParam> {};

TEST_P(UnexpectedTestSuite, Ex) {
  EXPECT_EQ(pairing_paren(GetParam().parens).error(), GetParam().message);
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  UnexpectedTestSuite,
  testing::ValuesIn(PARAMS),
  [](const testing::TestParamInfo<UnexpectedTestSuite::ParamType> &info) {
    using std::ranges::replace;

    auto test_name = string(info.param.message);
    // 空白やクォートが許容されてないので置換
    replace(test_name, ' ', '_');
    replace(test_name, '\'', '_');

    return test_name;
  }
);
