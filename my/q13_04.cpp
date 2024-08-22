#include "gtest/gtest.h"
#include <ranges>
#include <queue>
using std::vector;
using std::string_view;

// S: スタート
// G: ゴール
// .: 通路
// #: 壁

int shortest_path(const vector<string_view> &maze, const int H, const int W) {
  using std::optional;
  using std::queue;
  using std::pair;
  using std::views::iota;
  using std::initializer_list;

  // TODO: cartesian_product (C++23)
  pair<int, int> s, g;
  for (const auto i : iota(0, H)) {
    for (const auto j : iota(0, W)) {
      switch (maze.at(i).at(j)) {
        case 'S':
          s = {i, j}; break;
        case 'G':
          g = {i, j}; break;
        default:
          break;
        // TODO: validation
      }
    }
  }
  const auto [sx, sy] = s;
  const auto [gx, gy] = g;

  vector<vector<optional<int>>> dists(H, vector<optional<int>>(W));
  queue<pair<int, int>> todo; // BFS

  dists.at(sx).at(sy) = 0;
  todo.push(s);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();
    const auto [vx, vy] = v;

    for (const auto &[i, j] : initializer_list<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
      const pair<int, int> n = {vx + i, vy + j};
      const auto [nx, ny] = n;

      if (nx < 0 || ny < 0 || nx >= H || ny >= W) {
        continue;
      }

      if (maze.at(nx).at(ny) == '#') {
        continue;
      }

      if (!dists.at(nx).at(ny).has_value()) {
        dists.at(nx).at(ny) = dists.at(vx).at(vy).value() + 1;
        todo.push(n);
      }
    }
  }

  return dists.at(gx).at(gy).value();
}

TEST(TestSuite, Ex) {
  const vector<string_view> maze {
    ".#....#G",
    ".#.#....",
    "...#.##.",
    "#.##...#",
    "...###.#",
    ".#.....#",
    "...#.#..",
    "S.......",
  };

  EXPECT_EQ(shortest_path(maze, 8, 8), 16);
}

TEST(TestSuite, Impossible) {
  const vector<string_view> maze {
    ".#....#G",
    ".#.#...#", // Goalを壁で囲む
    "...#.##.",
    "#.##...#",
    "...###.#",
    ".#.....#",
    "...#.#..",
    "S.......",
  };

  EXPECT_THROW(shortest_path(maze, 8, 8), std::bad_optional_access);
}
