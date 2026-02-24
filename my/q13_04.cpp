#include "gtest/gtest.h"
#include <ranges>
#include <queue>
using std::vector;
using std::string_view;
using std::pair;
using std::optional;

struct Point {
  int x, y;
};

// S: スタート
// G: ゴール
// .: 通路
// #: 壁

constexpr pair<Point, Point> locate_start_and_goal(const vector<string_view> &maze, const Point dimensions) {
  // using std::string_view::npos;
  // using std::views::enumerate;
  using std::views::iota;
  using std::views::cartesian_product;

  const auto [H, W] = dimensions;

  optional<Point> s, g;

  // for (const auto &[i, row] : maze | enumerate) {
  //   size_t j;
  //   j = row.find('S');
  //   if (j != std::string_view::npos) {
  //     s = {i, j};
  //   }
  //   j = row.find('G');
  //   if (j != std::string_view::npos) {
  //     g = {i, j};
  //   }
  // }

  for (const auto &[i, j] : cartesian_product(iota(0, H), iota(0, W))) {
    switch (maze.at(i).at(j)) {
      case 'S': s = {i, j}; break;
      case 'G': g = {i, j}; break;
      default: break;
      // TODO: validation
    }
  }

  // start & goal point must exist
  [[assert: s.has_value() && g.has_value()]];

  return {s.value(), g.value()};
}

constexpr optional<int> shortest_path(const vector<string_view> &maze, const Point dimensions) {
  using std::queue;
  using std::initializer_list;

  const auto [s, g] = locate_start_and_goal(maze, dimensions);

  const auto [H, W] = dimensions;
  vector<vector<optional<int>>> dists(H, vector<optional<int>>(W));
  queue<Point> todo; // BFS

  dists.at(s.x).at(s.y) = 0;
  todo.push(s);

  while (!todo.empty()) {
    const Point v = todo.front();
    todo.pop();

    for (const auto &[i, j] : initializer_list<Point>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
      const Point n = {v.x + i, v.y + j};

      if (n.x < 0 || n.y < 0 || n.x >= H || n.y >= W) {
        continue;
      }

      if (maze.at(n.x).at(n.y) == '#') {
        continue;
      }

      if (!dists.at(n.x).at(n.y).has_value()) {
        dists.at(n.x).at(n.y) = dists.at(v.x).at(v.y).value() + 1;
        todo.push(n);
      }
    }
  }

  return dists.at(g.x).at(g.y);
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

  EXPECT_EQ(shortest_path(maze, {8, 8}), 16);
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

  EXPECT_EQ(shortest_path(maze, {8, 8}), std::nullopt);
}

TEST(TestSuite, StartNotExists) {
  const vector<string_view> maze {
    ".#....#G",
    ".#.#...#",
    "...#.##.",
    "#.##...#",
    "...###.#",
    ".#.....#",
    "...#.#..",
    "#.......",
  };

  EXPECT_DEATH(shortest_path(maze, {8, 8}), "");
}

TEST(TestSuite, GoalNotExists) {
  const vector<string_view> maze {
    ".#....##",
    ".#.#...#",
    "...#.##.",
    "#.##...#",
    "...###.#",
    ".#.....#",
    "...#.#..",
    "S.......",
  };

  EXPECT_DEATH(shortest_path(maze, {8, 8}), "");
}
