#include "gtest/gtest.h"
using std::vector;
using std::invalid_argument;

/*
  元の問題: 「選んだMコの小屋のうち2つの小屋の距離の最小値」の最大値を求める
  <=> 判定問題: 「選んだMコの小屋のうち2つの小屋の距離の最小値」をx以上にすることができるか
  <=> 判定問題: 選んだMコの小屋のすべての距離をx以上にすることができるか
  <=> 判定問題: すべての小屋の距離をx以上にして, 小屋をMコ選べるか
*/

// すべての小屋の距離をx以上にして, 選べる小屋の最大個数
int countx(const vector<int> a, const int x) {
  const int N = a.size();

  int prev = 0; // 前回選んだ小屋のindex
  int count = 1; // 小屋を選んだ個数

  // 貪欲法
  for (int i = 0; i < N; ++i) { // TODO: iota
    if (a.at(i) - a.at(prev) >= x) {
      ++count;
      prev = i;
    };
  }

  return count;
}

int cows(const vector<int> a, const int M) {
  const int N = a.size();

  if (M < 2 || M > N) {
    throw invalid_argument("2 <= M <= N required");
  }

  int left = 0; // 常にtrue
  int right = a.at(N - 1) + 1; // 常にfalse

  while (right - left > 1) {
    const int x = (left + right) / 2;

    if (countx(a, x) >= M) { // Mコ以上選べた => もっと距離を離せる => xはもっと大きい (true領域を更新)
      left = x;
    } else {  // Mコ選べなかった => 距離を離せていない => xはもっと小さい (false領域を更新)
      right = x;
    }
  }

  return left;
}

TEST(TestSuite, Ex) {
  EXPECT_EQ(cows({1, 2, 4, 8, 9}, 3), 3);
}

TEST(TestSuite, M_less_than_2) {
  EXPECT_THROW(cows({1, 2, 4, 8, 9}, 1), invalid_argument);
}

TEST(TestSuite, M_equal_to_2) {
  EXPECT_EQ(cows({1, 2, 4, 8, 9}, 2), 8);
}

TEST(TestSuite, M_equal_to_N) {
  EXPECT_EQ(cows({1, 2, 4, 8, 9}, 5), 1);
}

TEST(TestSuite, M_greater_than_N) {
  EXPECT_THROW(cows({1, 2, 4, 8, 9}, 6), invalid_argument);
}
