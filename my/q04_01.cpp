#include "gtest/gtest.h"

int tribo(int N) {
    // ベースケース
    switch(N) {
        case 0:
        case 1:
            return 0;
        case 2:
            return 1;
        default:
            break;
    }

    // 再帰呼び出し
    return tribo(N - 1) + tribo(N - 2) + tribo(N - 3);
}


TEST(TestCase, Test20) {
    EXPECT_EQ(tribo(20), 35890);
}

