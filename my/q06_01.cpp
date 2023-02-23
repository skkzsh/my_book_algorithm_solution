#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
using std::vector;

vector<int> ranking(const vector<int> a) {
    using namespace std::ranges;

    // aをsortしたvector
    vector<int> sorted = a;
    sort(sorted);

    vector<int> results(a.size());

    transform(a, results.begin(),
        [sorted](const int i) {
            return find(sorted, i) - sorted.begin();
            // find(sorted, a[i]) - sorted.begin();
            // find(a, sorted[i]) - a.begin();
         }
    );

    return results;
}

TEST(TestCase, Ex) {
    const vector<int> results = ranking({12, 43, 7, 15, 9});
    // sorted: 7, 9, 12, 15, 43

    EXPECT_EQ(results.at(0), 2);
    EXPECT_EQ(results.at(1), 4);
    EXPECT_EQ(results.at(2), 0);
    EXPECT_EQ(results.at(3), 3);
    EXPECT_EQ(results.at(4), 1);
}
