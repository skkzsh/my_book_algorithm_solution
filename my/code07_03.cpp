#include "gtest/gtest.h"
using std::vector;
using std::pair;
using pairs = vector<pair<int, int>>;

int min_push(pairs p) {
    int sum = 0;

    for (int i = p.size() - 1; i >= 0; --i) {
        int n = 1;
        while (p[i].first >= n * p[i].second) {
            ++n;
        }
        int count = n * p[i].second - p[i].first;
        std::cout << "i: "  << i << ", count: " << count << std::endl;

        for (int j = 0; j <= i; ++j) {
            p[j].first += count;
        }

        sum += count;
    }

    return sum;
}


TEST(TestCase, Ex1) {
    const pairs p {
        {3, 5},
        {2, 7},
        {9, 4},
    };

    EXPECT_EQ(min_push(p), 7);
}

TEST(TestCase, Ex2) {
    const pairs p {
        {3, 1},
        {4, 1},
        {5, 9},
        {2, 6},
        {5, 3},
        {5, 8},
        {9, 7},
    };

    EXPECT_EQ(min_push(p), 22);
}
