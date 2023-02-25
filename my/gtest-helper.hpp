#pragma once

#include "template.hpp"
using std::vector;


struct PairsIntParam {
    const Pairs<int> p;
    const int expected;
};

class PairsIntSuite : public ::testing::TestWithParam<PairsIntParam> {};


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
