#include "gtest/gtest.h"
#include "template.hpp"
#include <stack>

Pairs<int> pairing_paren(std::string_view parens) {
    Pairs<int> result;
    std::stack<int> st; // 左括弧の index を格納する stack

    for (size_t i = 0; i < parens.length() ; ++i) {
        switch (parens[i]) {
            case '(':
                st.push(i);
                break;
            case ')':
                if (st.empty()) { throw std::invalid_argument("Missing left paren to pair"); }
                result.push_back({st.top(), i});
                st.pop();
                break;
            default:
                throw std::invalid_argument("Something that isn't paren included");
        }
    }

    if (!st.empty()) { throw std::invalid_argument("Missing right paren to pair"); }
    return result;
}

// NOTE: assert順はアルゴリズムの出力結果に合わせている (右括弧の昇順)
TEST(TestCase, Q) {
    const Pairs<int> result = pairing_paren("(()(())())(()())");
    EXPECT_EQ(result.at(0).first,  1);
    EXPECT_EQ(result.at(0).second, 2);
    EXPECT_EQ(result.at(1).first,  4);
    EXPECT_EQ(result.at(1).second, 5);
    EXPECT_EQ(result.at(2).first,  3);
    EXPECT_EQ(result.at(2).second, 6);
    EXPECT_EQ(result.at(3).first,  7);
    EXPECT_EQ(result.at(3).second, 8);
    EXPECT_EQ(result.at(4).first,  0);
    EXPECT_EQ(result.at(4).second, 9);
    EXPECT_EQ(result.at(5).first,  11);
    EXPECT_EQ(result.at(5).second, 12);
    EXPECT_EQ(result.at(6).first,  13);
    EXPECT_EQ(result.at(6).second, 14);
    EXPECT_EQ(result.at(7).first,  10);
    EXPECT_EQ(result.at(7).second, 15);
}

TEST(TestCase, MissingLeftParen) {
    EXPECT_THROW(pairing_paren(")("), std::invalid_argument);
}

TEST(TestCase, MissingRightParen) {
    EXPECT_THROW(pairing_paren("(("), std::invalid_argument);
}

TEST(TestCase, NotParens) {
    EXPECT_THROW(pairing_paren("{}"), std::invalid_argument);
}
