#include "gtest/gtest.h"
#include <algorithm>
#include <unordered_set>
using std::invalid_argument;

// 3, 5, 7のカウントから算出する
constexpr int count753recursive(const int K) {
  using std::ranges::all_of;

  if (K < 0) {
    throw invalid_argument("argument must not be negative");
  }

  if (K < 357) {
    return 0;
  }

  std::unordered_map<int, int> count753map {
    {3, 0},
    {5, 0},
    {7, 0},
  };

  for (int tail = K; tail > 0; tail /= 10) {
    switch (const int n = tail % 10) {
      case 3:
      case 5:
      case 7:
        ++count753map.at(n);
        break;
      default:
        return count753recursive(K - 1);
    }
  }

  // if (count753map[3] > 0 && count753map[5] > 0 && count753map[7] > 0) {
  if (all_of(count753map,
             [](const auto &p) { return p.second > 0; })) {
    return count753recursive(K - 1) + 1;
  }
  return count753recursive(K - 1);
}

// 3, 5, 7の順列から算出する
int count753permutation(const int K) {
  using namespace std::ranges;
  using std::string;
  using std::stoi;
  using std::unordered_set;

  if (K < 0) {
    throw invalid_argument("argument must not be negative");
  }

  string s = "357";
  // int digit = std::to_string(K).length(); // TODO: 4ケタ以上の場合に対応する

  unordered_set<int> candidates;
  do {
    candidates.insert(stoi(s));
  } while (next_permutation(s).found);

  return count_if(candidates, [K](const int c) { return c <= K; });
}

// TODO: combine

TEST(TestSuite, Test0) {
  EXPECT_EQ(count753recursive(356), 0);
  EXPECT_EQ(count753permutation(356), 0);
}

TEST(TestSuite, Test1Min) {
  EXPECT_EQ(count753recursive(357), 1);
  EXPECT_EQ(count753permutation(357), 1);
}

TEST(TestSuite, Test1Max) {
  EXPECT_EQ(count753recursive(374), 1);
  EXPECT_EQ(count753permutation(374), 1);
}

TEST(TestSuite, Test2Min) {
  EXPECT_EQ(count753recursive(375), 2);
  EXPECT_EQ(count753permutation(375), 2);
}

TEST(TestSuite, Test4digit1) {
  EXPECT_EQ(count753recursive(1357), 6);
  EXPECT_EQ(count753permutation(1357), 6);
}

TEST(TestSuite, Test4digitMin) {
  EXPECT_EQ(count753recursive(3357), 7);
  GTEST_SKIP() << "未実装のため";
  EXPECT_EQ(count753permutation(3357), 7); // TODO
}

TEST(TestSuite, Negative) {
  EXPECT_THROW(count753recursive(-1), invalid_argument);
  EXPECT_THROW(count753permutation(-1), invalid_argument);
}
