#ifndef FRACTION_FIXTURE_H
#define FRACTION_FIXTURE_H

#include "stdafx.h"
#include "../Course_work/fraction.h"

class FractionTest : public testing::Test {
protected:
    void SetUp() override {
        zero = Fraction(0);
        half = Fraction(1, 2);
        minusHalf = Fraction(-1, 2);
        minusOne = Fraction(-1);
    }

    Fraction def;
    Fraction zero;
    Fraction half;
    Fraction minusHalf;
    Fraction minusOne;
};

#endif // !FRACTION_FIXTURE_H
