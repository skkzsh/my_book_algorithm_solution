#pragma once

#include "template.hpp"
using std::vector;


struct PairsIntParam {
    const Pairs<int> p;
    const int expected;

    PairsIntParam(
        const Pairs<int> p, const int expected
    ) :
        p(p), expected(expected)
    {}
};

class PairsIntSuite : public ::testing::TestWithParam<PairsIntParam> {};


struct PairVectorIntParam {
    const vector<int> a;
    const vector<int> b;
    const int expected;

    PairVectorIntParam(
        const vector<int> a, const vector<int> b, const int expected
    ) :
        a(a), b(b), expected(expected)
    {}
};

class PairVectorIntSuite : public ::testing::TestWithParam<PairVectorIntParam> {};


struct PairPairsIntParam {
    const Pairs<int> a;
    const Pairs<int> b;
    const int expected;

    PairPairsIntParam(
        const Pairs<int> a, const Pairs<int> b, const int expected
    ) :
        a(a), b(b), expected(expected)
    {}
};

class PairPairsIntSuite : public ::testing::TestWithParam<PairPairsIntParam> {};
