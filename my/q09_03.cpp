#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "template.hpp"
#include <stack>
using ::testing::ElementsAreArray;
using ::testing::Pair;
using std::invalid_argument;

Pairs<int> pairing_paren(std::string_view parens) {

    Pairs<int> result;
    std::stack<int> st; // 左括弧の index を格納する stack

    // TODO: using iota
    for (size_t i = 0; i < parens.length() ; ++i) {
        switch (parens.at(i)) {
            case '(':
                st.push(i);
                break;
            case ')':
                if (st.empty()) { throw invalid_argument("Missing left paren to pair"); }
                result.push_back({st.top(), i});
                st.pop();
                break;
            default:
                throw invalid_argument("Something that isn't paren included");
        }
    }

    if (!st.empty()) { throw invalid_argument("Missing right paren to pair"); }
    return result;
}

// NOTE: assert順はアルゴリズムの出力結果に合わせている (右括弧の昇順)
TEST(TestCase, Q) {
   EXPECT_THAT(pairing_paren("(()(())())(()())"),
       ElementsAreArray({
           Pair( 1,  2),
           Pair( 4,  5),
           Pair( 3,  6),
           Pair( 7,  8),
           Pair( 0,  9),
           Pair(11, 12),
           Pair(13, 14),
           Pair(10, 15),
       })
   );
}

TEST(TestCase, MissingLeftParen) {
    EXPECT_THROW(pairing_paren(")("), invalid_argument);
}

TEST(TestCase, MissingRightParen) {
    EXPECT_THROW(pairing_paren("(("), invalid_argument);
}

TEST(TestCase, NotParens) {
    EXPECT_THROW(pairing_paren("{}"), invalid_argument);
}
