#pragma once

#include "gtest/gtest.h"
#include "template.hpp"
using std::vector;
using std::string_view;
using std::string;
using std::pair;
using std::tuple;


struct PairsIntParam {
    const Pairs<int> p;
    const int expected;
};

class PairsIntSuite : public ::testing::TestWithParam<PairsIntParam> {};

struct PairsIntIntParam {
    const Pairs<int> E;
    const int N;
    const int expected;
};

class PairsIntIntSuite : public ::testing::TestWithParam<PairsIntIntParam> {};


template<class T> struct PairIntParam {
    const T a;
    const T b;
    const int expected;
};

class PairVectorIntSuite : public ::testing::TestWithParam<PairIntParam<vector<int>>> {};
class PairPairsIntSuite : public ::testing::TestWithParam<PairIntParam<Pairs<int>>> {};

class PairIntSuite : public ::testing::TestWithParam<pair<int, int>> {};
class TrioStringSuite : public ::testing::TestWithParam<tuple<string_view, string_view, string_view>> {};
class PairStringSuite : public ::testing::TestWithParam<pair<string_view, string_view>> {};

// TODO: NOT header
string PrintToFirstParamName(const testing::TestParamInfo<PairIntSuite::ParamType>& info) {
    return std::to_string(info.param.first);
}

string PrintToSecondParamName(const testing::TestParamInfo<PairStringSuite::ParamType>& info) {
    return (string) info.param.second;
}
