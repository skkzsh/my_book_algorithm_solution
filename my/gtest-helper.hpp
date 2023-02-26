#pragma once

#include "gtest/gtest.h"
using std::string_view;
using std::string;
using std::pair;


template<class T> struct SingleTestParam {
    const T x;
    const int expected;
    string_view test_name = "default";
};

template<class T> struct PairTestParam {
    const T a;
    const T b;
    const int expected;
    string_view test_name = "default";
};


class PairStringSuite : public ::testing::TestWithParam<pair<string_view, string_view>> {};

// TODO: NOT header
string PrintToSecondParamName(const testing::TestParamInfo<PairStringSuite::ParamType>& info) {
    return (string) info.param.second;
}
