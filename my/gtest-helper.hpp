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


// TODO: template
struct PairVectorIntParam {
    const vector<int> a;
    const vector<int> b;
    const int expected;
};

class PairVectorIntSuite : public ::testing::TestWithParam<PairVectorIntParam> {};


struct PairPairsIntParam {
    const Pairs<int> a;
    const Pairs<int> b;
    const int expected;
};

class PairPairsIntSuite : public ::testing::TestWithParam<PairPairsIntParam> {};


class TrioStringSuite : public ::testing::TestWithParam<std::tuple<string_view, string_view, string_view>> {};
class PairStringSuite : public ::testing::TestWithParam<std::pair<string_view, string_view>> {};

string PrintToSecondParamName(const testing::TestParamInfo<PairStringSuite::ParamType>& info) {
    return (string) info.param.second;
}
