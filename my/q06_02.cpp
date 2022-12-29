#include "gtest/gtest.h"
#include <algorithm>
#include <ranges>
using std::vector;

// O(N ^ 3)
int festival_simple(const vector<vector<int>> z) {
    int count = 0;

    for (const int a : z[0]) {
        for (const int b : z[1]) {
            if (a < b) {
                for (int c : z[2]) {
                    if (b < c) {
                        count++;
                    }
                }
                // count += std::ranges::count_if(z[2], [b](int c){ return b < c; });
            }
        }
    }

    return count;
}

// O(N log N)
int festival_binary(vector<vector<int>> z) {
    using namespace std::ranges;

    for (const int i : std::views::iota(0, 3)) {
        sort(z[i]);
    }

    int count = 0;

    for (const int b : z[1]) {
        count += (lower_bound(z[0], b) - z[0].begin()) // a[i] >= b となる最小のi <=> a[i - 1] < b <= a[i] => 数は (i - 1) - 0 + 1 = iコ
                    * (z[2].end() - upper_bound(z[2], b)); // c[i] > b となる最小のi => 数は N - i + 1 => c.end() - i
        // count += (lower_bound(z[0], b) - z[0].begin())
        //             * (N - (upper_bound(z[2], b) - z[2].begin()));
    }

    return count;
}


TEST(TestCase, Ex1) {
    const vector<vector<int>> z {
        {1, 5},
        {2, 4},
        {3, 6},
    };

    EXPECT_EQ(festival_simple(z), 3);
    EXPECT_EQ(festival_binary(z), 3);
}

TEST(TestCase, Ex2) {
    const vector<vector<int>> z {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
    };

    EXPECT_EQ(festival_simple(z), 27);
    EXPECT_EQ(festival_binary(z), 27);
}

TEST(TestCase, Ex3) {
    const vector<vector<int>> z {
        {3, 14, 159, 2, 6, 53},
        {58, 9, 79, 323, 84, 6},
        {2643, 383, 2, 79, 50, 288},
    };

    EXPECT_EQ(festival_simple(z), 87);
    EXPECT_EQ(festival_binary(z), 87);
}
