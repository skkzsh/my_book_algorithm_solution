#include "gtest/gtest.h"
#include <algorithm>
#include "template.hpp"
using std::pair;

template<class T> T remain(const pair<T, T> p) {
    return p.second - p.first;
}

bool can_done(Pairs<int> tasks) { // {d, t}
    using std::ranges::sort;
    sort(tasks, [](const auto p, auto const q) {
        return remain(p) < remain(q);
    });

    int now = 0;

    for (const auto& task : tasks) {
        // std::cout << task << ' ' << task << std::endl; // debug
        now += task.first;
        if (now > task.second) {
            return false;
        }
    }

    return true;
}


TEST(TestCase, Ex1) {
    const Pairs<int> tasks {
        {2, 4},
        {1, 9},
        {1, 8},
        {4, 9},
        {3, 12},
    };

    EXPECT_EQ(can_done(tasks), true);
}

TEST(TestCase, Ex2) {
    const Pairs<int> tasks {
        {334, 1000},
        {334, 1000},
        {334, 1000},
    };

    EXPECT_EQ(can_done(tasks), false);
}

TEST(TestCase, Ex3) {
    const Pairs<int> tasks {
        { 384,  8895  },
        { 1725, 9791  },
        { 170,  1024  },
        { 4,    11105 },
        { 2,    6     },
        { 578,  1815  },
        { 702,  3352  },
        { 143,  5141  },
        { 1420, 6980  },
        { 24,   1602  },
        { 849,  999   },
        { 76,   7586  },
        { 85,   5570  },
        { 444,  4991  },
        { 719,  11090 },
        { 470,  10708 },
        { 1137, 4547  },
        { 455,  9003  },
        { 110,  9901  },
        { 15,   8578  },
        { 368,  3692  },
        { 104,  1286  },
        { 3,    4     },
        { 366,  12143 },
        { 7,    6649  },
        { 610,  2374  },
        { 152,  7324  },
        { 4,    7042  },
        { 292,  11386 },
        { 334,  5720  },
    };

    EXPECT_EQ(can_done(tasks), true);
}
