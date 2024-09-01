#pragma once

#include <vector>
#include <print>

using std::vector;
using std::pair;
using std::tuple;

template <class T> constexpr void chmin(T &a, const T b) {
  a = std::min(a, b);
}

template <class T> constexpr void chmax(T &a, const T b) {
  a = std::max(a, b);
}

// TODO: concept
constexpr void print2d(const auto cc) {
  using std::print;
  using std::println;

  println("print2d start");
  for (const auto &c : cc) {
    // println("{}", c | join_with(" ")); // TODO
    for (const auto &x : c) {
      print("{} ", x);
    }
    println("");
  }
  println("print2d end");
}

template <class T> using Pairs = vector<pair<T, T>>;

template <typename... Args>
auto sum_tuple(const tuple<Args...> &t) {
    using std::apply;

    return apply([](auto&&... args) {
        return (args + ...);
    }, t);
}
