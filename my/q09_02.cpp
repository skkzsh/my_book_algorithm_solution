#include "gtest/gtest.h"
#include <ranges>
#include <algorithm>
#include <stack>
#include <expected>
using std::expected;
using std::unexpected;
using std::string_view;
using std::string;

constexpr expected<double, string> polish(const string_view expr) {
  std::stack<double> st;

  for (const char c : expr) {
    if ('0' <= c && c <= '9') {
      st.push(c - '0');
    } else {
      if (st.empty()) { return unexpected("No operand exist"); }
      const double a = st.top();
      st.pop();

      if (st.empty()) { return unexpected("One operand only exist"); }
      const double b = st.top();
      st.pop();

      switch (c) {
        case '+': st.push(b + a); break;
        case '-': st.push(b - a); break;
        case '*': st.push(b * a); break;
        case '/': st.push(b / a); break;
        default: return unexpected("Argument must be number or operator");
      }
    }
  }

  if (st.size() != 1) { return unexpected("Invalid expression"); }
  return st.top();
}


TEST(TestSuite, Q) {
  EXPECT_EQ(polish("34+12-*"), -7);
}

constexpr struct UnexpectedTestParam {
  const string_view expr;
  const string_view message;
} PARAMS[] {
  {"34+12-?",  "Argument must be number or operator"},
  {"+12-*",    "No operand exist"},
  {"4+12-*",   "One operand only exist"},
  {"134+12-*", "Invalid expression"}, // Too many numbers
  {"34+12-*/", "One operand only exist"}, // Too many operators
};

class UnexpectedTestSuite : public testing::TestWithParam<UnexpectedTestParam> {};

TEST_P(UnexpectedTestSuite, Ex) {
  EXPECT_EQ(polish(GetParam().expr).error(), GetParam().message);
}

INSTANTIATE_TEST_SUITE_P(
  Inst,
  UnexpectedTestSuite,
  testing::ValuesIn(PARAMS),
  [](const testing::TestParamInfo<UnexpectedTestSuite::ParamType> &info) {
    using std::ranges::replace;
    using std::to_string;

    // インデックスを付与してユニーク化
    auto test_name = to_string(info.index) + '_' + string(info.param.message);
    // 空白が許容されてないので置換
    replace(test_name, ' ', '_');

    return test_name;
  }
);
