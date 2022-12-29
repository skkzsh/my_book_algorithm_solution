#include "gtest/gtest.h"
using std::vector;

int festival(const vector<vector<int>> z) {
    int count = 0;

    for (int a : z[0]) {
        for (int b : z[1]) {
            if (a < b) {
                for (int c : z[2]) {
                    if (b < c) {
                        count++;
                    }
                }
            }
        }
    }

    return count;
}


TEST(TestCase, Ex1) {
    const vector<vector<int>> z {
        {1, 5},
        {2, 4},
        {3, 6},
    };

    EXPECT_EQ(festival(z), 3);
}

TEST(TestCase, Ex2) {
    const vector<vector<int>> z {
        {1, 1, 1},
        {2, 2, 2},
        {3, 3, 3},
    };

    EXPECT_EQ(festival(z), 27);
}

TEST(TestCase, Ex3) {
    const vector<vector<int>> z {
        {3, 14, 159, 2, 6, 53},
        {58, 9, 79, 323, 84, 6},
        {2643, 383, 2, 79, 50, 288},
    };

    EXPECT_EQ(festival(z), 87);
}
