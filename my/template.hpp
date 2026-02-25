#pragma once

#include <vector>
#include <print>
// #include <concepts>

using std::vector;
using std::pair;
using std::tuple;

// <totally_ordered T>
template <class T> constexpr void chmin(T &a, const T b) {
  a = std::min(a, b);
}

template <class T> constexpr void chmax(T &a, const T b) {
  a = std::max(a, b);
}

// 更新があれば, trueを返す版
template <class T> constexpr bool chminb(T &a, const T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
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

// template <typename T>
// concept OptionalLike = requires(T opt) {
//   { opt.value() };
// };

template <class T> using Pairs = vector<pair<T, T>>;

template <typename... Args>
constexpr auto sum_tuple(const tuple<Args...> &t) {
    using std::apply;

    return apply([](auto&&... args) {
        return (args + ...);
    }, t);
}
