#include "gtest/gtest.h"
#include <algorithm>
using std::vector;
using namespace std::ranges;

// O(N^2 * log N)
int product_th_simple(const vector<int> a, const vector<int> b, const int K) {
    vector<int> p; // (a.size() * b.size())
    for (const int i : a) {
        for (const int j : b) {
            p.push_back(i * j);
        }
    }
    sort(p);
    return p[K - 1];
}

/*
元の問題: a[i] * b[j] の中でK番目に小さい値をを求める
<=> 判定問題: a[i] * b[j] のうちx以下がKコ (以上) あるかどうか
*/

// a[i] * b[j] <= x の数を返す関数
// a, bはソート済が前提
// O(N * log N)
int countx(const vector<int> a, const vector<int> b, const int x) {
    /*
    a[i] を固定して b[j] <= x / a[i] となる最大のjを求める
    <=> a[i] を固定して b[j] > x / a[i] となる最小のjを求める
    <=> b[j - 1] <= x / a[i] < b[j]

    j - 1 までで (j - 1) - 0 + 1 = jコ
    */

    int count = 0;
    for (const int m : a) {
        count += upper_bound(b, x / m) - b.begin();
    }
    return count;
}

// O(N * log N * log C)
int product_th_binary(vector<int> a, vector<int> b, const int K) {
    sort(a);
    sort(b);

    if (a[0] <= 0 || b[0] <= 0) {
        throw std::invalid_argument("a and b must be positive numbers");
    }

    int left = 0; // 常にfalse (∵ a, b > 0)
    int right = a[a.size() - 1] * b[b.size() - 1]; // 常にtrue

    while (right - left > 1) {
        const int x = (left + right) / 2;

        if (countx(a, b, x) >= K) {
            right = x;
        } else {
            left = x;
        }
    }

    return right;
}

TEST(TestCase, Ex1) {
    EXPECT_EQ(product_th_simple({2, 3}, {3, 5}, 3), 10);
    EXPECT_EQ(product_th_binary({2, 3}, {3, 5}, 3), 10);
}

TEST(TestCase, Ex2) {
    EXPECT_EQ(product_th_simple({1, 2, 1}, {2, 1, 2}, 7), 2);
    EXPECT_EQ(product_th_binary({1, 2, 1}, {2, 1, 2}, 7), 2);
}

TEST(TestCase, Zero) {
    EXPECT_THROW(product_th_binary({1, 0, 1}, {1, 1, 1}, 1), std::invalid_argument);
    EXPECT_THROW(product_th_binary({1, 1, 1}, {1, 1, 0}, 1), std::invalid_argument);
}
