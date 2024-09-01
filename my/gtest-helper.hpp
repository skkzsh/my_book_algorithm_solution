#pragma once

#include "gtest/gtest.h"
using ::testing::TestWithParam;
using ::testing::TestParamInfo;
using std::string_view;
using std::string;
using std::pair;


template <class T> struct SingleTestParam {
  const T x;
  const int gold;
  string_view test_name = "default";
};

template <class T> struct PairTestParam {
  const T a;
  const T b;
  const unsigned int gold;
  string_view test_name = "default";
};


class PairStringSuite : public TestWithParam<pair<string_view, string_view>> {};

// TODO: NOT header
string PrintToSecondParamName(const TestParamInfo<PairStringSuite::ParamType> &info) {
  return string(info.param.second);
}
