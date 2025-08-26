#include "stdafx.h"
#include "matrix.h"
#include "fraction.h"

class Fixture : public testing::Test {
protected:
    void SetUp() override {
        zero.resize(1, 1);
    }
    ~Fixture() {}

    Matrix<Fraction> zero;
};