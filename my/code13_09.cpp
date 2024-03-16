#include "gmock/gmock.h"
#include "graph.hpp"
using std::optional;
using ::testing::ElementsAreArray;
using ::testing::FieldsAre;

constexpr int NA = -1;

struct Vertex {
  int depth = NA;
  int size = NA;
};

// NOTE: 最短経路のような導出となっている
void recursive_search(const vector<multiset<int>> &G, const int v, vector<Vertex> &V) {
  V.at(v).size = 1;

  for (const auto n : G.at(v)) {
    if (V.at(n).depth == NA) {
      V.at(n).depth = V.at(v).depth + 1;
      recursive_search(G, n, V);
      V.at(v).size += V.at(n).size;
    }
  }
}

// E: 木 (連結, サイクルなし) TODO
vector<Vertex> tree(const multimap<int, int> &E, const int root) {
  using std::ranges::transform;

  const auto G = to_adjacency_list(E);

  vector<Vertex> V(G.size());
  V.at(root).depth = 0;

  recursive_search(G, root, V);

  return V;
}

// TODO: test case
TEST(TestSuite, Ex) {
  const multimap<int, int> T {
    {0, 1},
    {0, 2},
    {1, 3},
    {1, 4},
    {1, 5},
    {4, 7},
    {4, 8},
    {2, 6},
    {6, 9},
  };

  EXPECT_THAT(tree(T, 0), ElementsAreArray({
    // AllOf(Field(&Vertex::depth, 0), Field(&Vertex::size, 10)),
    FieldsAre(0, 10),
    FieldsAre(1, 6),
    FieldsAre(1, 3),
    FieldsAre(2, 1),
    FieldsAre(2, 3),
    FieldsAre(2, 1),
    FieldsAre(2, 2),
    FieldsAre(3, 1),
    FieldsAre(3, 1),
    FieldsAre(3, 1),
  }));
}
