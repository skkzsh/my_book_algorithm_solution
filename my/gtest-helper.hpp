#pragma once

#include "gtest/gtest.h"


template <class T> struct SingleTestParam {
  const T x;
  const int gold;
  std::string_view test_name = "default";
};

template <class T> struct PairTestParam {
  const T a;
  const T b;
  const unsigned int gold;
  std::string_view test_name = "default";
};
