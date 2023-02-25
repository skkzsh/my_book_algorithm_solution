#pragma once

#include "gtest/gtest.h"
#include "template.hpp"
using std::vector;
using std::string_view;
using std::string;


struct PairsIntParam {
    const Pairs<int> p;
    const int expected;
};

class PairsIntSuite : public ::testing::TestWithParam<PairsIntParam> {};


template<class T> struct PairIntParam {
    const T a;
    const T b;
    const int expected;
};

class PairVectorIntSuite : public ::testing::TestWithParam<PairIntParam<vector<int>>> {};
class PairPairsIntSuite : public ::testing::TestWithParam<PairIntParam<Pairs<int>>> {};


class TrioStringSuite : public ::testing::TestWithParam<std::tuple<string_view, string_view, string_view>> {};
class PairStringSuite : public ::testing::TestWithParam<std::pair<string_view, string_view>> {};

// TODO: NOT header
string PrintToSecondParamName(const testing::TestParamInfo<PairStringSuite::ParamType>& info) {
    return (string) info.param.second;
}
