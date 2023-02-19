#include "gtest/gtest.h"
#include <cmath>

using std::tuple;
using std::pair;

template<class T> using Constant = tuple<T, T, T>;

constexpr double EPS = 1e-6; // 精度

double func(const double t, const Constant<int> constant) {
    using std::sin;
    using std::numbers::pi;

    const auto [A, B, C] = constant;
    return A * t + B * sin(C * t * pi) - 100;
}

double bisection(const Constant<int> constant, const pair<double, double> interval) {
   using std::invalid_argument;

    auto [left, right] = interval;

    if (left >= right) {
        throw invalid_argument("left must be less than right");
    }

    // debug
    // std::cout << func(left, constant) << ' ' << func(right, constant) << std::endl;

    // func(left) < 0 かつ func(right) > 0 が必要条件
    if (func(left, constant) >= 0 || func(right, constant) <= 0) {
        throw invalid_argument("func(left) < 0 and func(right) > 0 required");
    }

    while (right - left > EPS) {
        const double t = (left + right) / 2;

        if (func(t, constant) >= 0) {
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
