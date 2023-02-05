#include "gtest/gtest.h"
#include <algorithm>
using std::vector;

// 前提
// a[0] <= a[i]
// b[0] <= b[j]
// 定義
// a[i] < b[0]
// a[0] < b[j]
// =>
// a[0] <= a[i] < b[0] <= b[j]
// =>
// a[0] < b[0]
// a[i] < b[j]
// => 交換可能

int max_pairing(vector<int> a, vector<int> b) {
    using std::sort; // TODO: using ranges
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0;
    for (const int m : b) {
        if (a.at(i) < m) {
            ++i;
        }
    }
    return i;
}


TEST(TestCase, Ex1) {
    const vector<int> a {2, 3, 1};
    const vector<int> b {4, 0, 5};
    EXPECT_EQ(max_pairing(a, b), 2);
}

TEST(TestCase, Ex2) {
    const vector<int> a {0, 1, 5};
    const vector<int> b {2, 3, 4};
    EXPECT_EQ(max_pairing(a, b), 2);
}

TEST(TestCase, Ex3) {
    const vector<int> a {2, 3};
    const vector<int> b {0, 1};
    EXPECT_EQ(max_pairing(a, b), 0);
}

TEST(TestCase, Ex4) {
    const vector<int> a {0, 7, 2, 4, 1};
    const vector<int> b {8, 6, 5, 9, 3};
    EXPECT_EQ(max_pairing(a, b), 5);
}

TEST(TestCase, Ex5) {
    const vector<int> a {0, 1, 5, 6, 7};
    const vector<int> b {2, 3, 4, 8, 9};
    EXPECT_EQ(max_pairing(a, b), 4);
}
