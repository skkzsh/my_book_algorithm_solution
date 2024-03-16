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

template<class T> constexpr void print2d(const vector<vector<T>> vv) {
  using std::cout;
  using std::endl;
  // using std::println;

  cout << "print2d start" << endl;
  for (const vector<T> v : vv) {
    for (const T i : v) {
      cout << i << ' ';
    }
    cout << endl;
  }
  cout << "print2d end" << endl;
}

template<class T> using Pairs = vector<pair<T, T>>;
