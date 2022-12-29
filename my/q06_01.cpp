#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
using std::vector;

vector<int> ranking(const vector<int> a) {
    using namespace std::ranges;

    // aをsortしたvector
    vector<int> sorted = a;
    sort(sorted);

    vector<int> result(a.size());

    transform(a, result.begin(),
        [sorted](const int i) {
            return find(sorted, i) - sorted.begin();
            // find(sorted, a[i]) - sorted.begin();
            // find(a, sorted[i]) - a.begin();
         }
    );

    return result;
}

TEST(TestCase, Ex) {
    const vector<int> result = ranking({12, 43, 7, 15, 9});
    // sorted: 7, 9, 12, 15, 43

    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 4);
    EXPECT_EQ(result[2], 0);
    EXPECT_EQ(result[3], 3);
    EXPECT_EQ(result[4], 1);
}
