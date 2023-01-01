#include "gtest/gtest.h"
#include <cmath>

using std::tuple;
using std::pair;

constexpr double EPS = 1e-6; // 精度

double func(const double t, const tuple<int, int, int> constants) {
    using std::sin;
    using std::numbers::pi;

    const auto [A, B, C] = constants;
    return A * t + B * sin(C * t * pi) - 100;
}

double bisection(const tuple<int, int, int> constants, const pair<double, double> interval) {
    auto [left, right] = interval;

    if (left >= right) {
        throw std::invalid_argument("left must be less than right");
    }

    // debug
    // std::cout << func(left, constants) << ' ' << func(right, constants) << std::endl;

    // func(left) < 0 かつ func(right) > 0 が必要条件
    if (func(left, constants) >= 0 || func(right, constants) <= 0) {
        throw std::invalid_argument("func(left) < 0 and func(right) > 0 required");
    }

    while (right - left > EPS) {
        const double t = (left + right) / 2;

        if (func(t, constants) >= 0) {
            right = t;
        } else {
            left = t;
        }
    }

    return right;
}

// 解は複数あるが, 返却値はそのうちの1つであり, 探索範囲によって変わることに注意

TEST(TestCase, Ex1) {
    EXPECT_NEAR(bisection({1, 1, 1}, {0, 200}), 100, EPS);
}

TEST(TestCase, Ex2) {
    EXPECT_NEAR(bisection({53, 82, 49}, {1.58, 1.65}), 1.63372043395339, EPS);
}
