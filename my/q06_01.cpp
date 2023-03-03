#include "gmock/gmock.h"
#include <algorithm>
#include <ranges>
using ::testing::ElementsAreArray;
using std::vector;

constexpr vector<int> ranking(const vector<int> a) {
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

TEST(TestSuite, Ex) {
    EXPECT_THAT(ranking({12, 43, 7, 15, 9}), ElementsAreArray({2, 4, 0, 3, 1}));
    // sorted: 7, 9, 12, 15, 43
}
