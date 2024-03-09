#include "gmock/gmock.h"
#include <queue>
#include <ranges>
using ::testing::ElementsAreArray;
using std::vector;

vector<unsigned int> BFS(const vector<vector<unsigned int>> &G, const unsigned int s) {
  using std::optional;
  using std::ranges::transform;

  vector<optional<unsigned int>> dists(G.size());
  std::queue<unsigned int> todo;

  dists.at(s) = 0;
  todo.push(s);

  while (!todo.empty()) {
    const auto v = todo.front();
    todo.pop();

    for (const auto x : G.at(v)) {
      if (!dists.at(x).has_value()) {
        dists.at(x) = dists.at(v).value() + 1;
        todo.push(x);
      }
    }
  }

  // optionalはがし
  vector<unsigned int> results(G.size());
  transform(dists, results.begin(),
            [](const auto x) { return x.value(); }  // TODO: optional<auto> or auto
            );

  // TODO: C++23
  // using std::views::transform;
  // using std::ranges::to;

  return results;
}

TEST(TestSuite, Ex) {
  const vector<vector<unsigned int>> G {
    {1, 2, 4},
    {0, 3, 4, 8},
    {0, 5},
    {1, 7, 8},
    {0, 1, 8},
    {2, 6, 8},
    {5, 7},
    {3, 6},
    {1, 3, 4, 5},
  };

  EXPECT_THAT(BFS(G, 0), ElementsAreArray({0, 1, 1, 2, 1, 2, 3, 3, 2}));
}
