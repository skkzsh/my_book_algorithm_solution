#pragma once

#include <vector>
#include <iostream>
// #include <print> // TODO: C++23

using std::vector;
using std::pair;

template<class T> constexpr void chmin(T& a, const T b) {
  a = std::min(a, b);
}

template<class T> constexpr void chmax(T& a, const T b) {
  a = std::max(a, b);
}

// TODO: concept
template<class CC> constexpr void print2d(const CC cc) {
  using std::cout;
  using std::endl;
  // using std::println;

  cout << "print2d start" << endl;
  for (const auto c : cc) {
    for (const auto x : c) {
      cout << x << ' ';
    }
    cout << endl;
  }
  cout << "print2d end" << endl;
}

template<class T> using Pairs = vector<pair<T, T>>;
