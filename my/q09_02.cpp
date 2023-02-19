#include "gtest/gtest.h"
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

TEST(TestCase, Q) {
    EXPECT_EQ(polish("34+12-*"), -7);
}

TEST(TestCase, InvalidOperator) {
    EXPECT_THROW(polish("34+12-?"), invalid_argument);
}

TEST(TestCase, NoOperandExist) {
    EXPECT_THROW(polish("+12-*"), invalid_argument);
}

TEST(TestCase, OneOperandOnlyExist) {
    EXPECT_THROW(polish("4+12-*"), invalid_argument);
}

TEST(TestCase, TooManyNumbers) {
    EXPECT_THROW(polish("134+12-*"), invalid_argument);
}

TEST(TestCase, TooManyOperators) {
    EXPECT_THROW(polish("34+12-*/"), invalid_argument);
}
