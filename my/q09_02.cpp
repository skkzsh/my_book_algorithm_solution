#include "gtest/gtest.h"
#include "gtest-helper.hpp"
#include <stack>
using std::invalid_argument;

double polish(std::string_view expr) {
    std::stack<double> st;

    for (const char c : expr) {
        if ('0' <= c && c <= '9') {
            st.push(c - '0');
        } else {
            if (st.empty()) { throw invalid_argument("No operand exist"); }
            const double a = st.top();
            st.pop();

            if (st.empty()) { throw invalid_argument("One operand only exist"); }
            const double b = st.top();
            st.pop();

            switch (c) {
                case '+': st.push(b + a); break;
                case '-': st.push(b - a); break;
                case '*': st.push(b * a); break;
                case '/': st.push(b / a); break;
                default: throw invalid_argument("Argument must be number or operator");
            }
        }
    }

    if (st.size() != 1) { throw invalid_argument("Invalid expression"); }
    return st.top();
}


TEST(TestSuite, Q) {
    EXPECT_EQ(polish("34+12-*"), -7);
}

TEST_P(PairStringSuite, Invalid) {
    EXPECT_THROW(polish(GetParam().first), invalid_argument);
}

constexpr std::pair<string_view, string_view> params[] {
    {"34+12-?",  "InvalidOperator"},
    {"+12-*",    "NoOperandExist"},
    {"4+12-*",   "OneOperandOnlyExist"},
    {"134+12-*", "TooManyNumbers"},
    {"34+12-*/", "TooManyOperators"},
};

INSTANTIATE_TEST_SUITE_P(
    Inst,
    PairStringSuite,
    ::testing::ValuesIn(params),
    PrintToSecondParamName
);
