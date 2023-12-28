#include "gtest/gtest.h"
using std::vector;
using std::tuple;

template<class T> using Trios = vector<tuple<T, T, T>>;

// TODO: 実装

// N: Zと整合性が取れていること
// Z: 0以上の連番であること
bool exists(const int N, const Trios<int> &Z) {
  throw std::logic_error("未実装: " + N + Z.size());
}

class TestSuite : public ::testing::Test {
 protected:
  void SetUp() override {
    GTEST_SKIP() << "未実装のため";
  }
};

TEST_F(TestSuite, Ex1) {
  const Trios<int> Z {
    {1, 2, 1},
    {2, 3, 1},
    {1, 3, 2},
  };
  EXPECT_TRUE(exists(3, Z));
}

TEST_F(TestSuite, Ex2) {
  const Trios<int> Z {
    {1, 2, 1},
    {2, 3, 1},
    {1, 3, 5},
  };
  EXPECT_FALSE(exists(3, Z));
}

TEST_F(TestSuite, Ex3) {
  const Trios<int> Z {
    {2, 1, 1},
    {2, 3, 5},
    {3, 4, 2},
  };
  EXPECT_TRUE(exists(4, Z));
}

TEST_F(TestSuite, Ex4) {
  const Trios<int> Z {
    {8, 7, 100},
    {7, 9, 100},
    {9, 8, 100},
  };
  EXPECT_FALSE(exists(10, Z));
}

TEST_F(TestSuite, Ex5) {
  EXPECT_TRUE(exists(100, {}));
}
