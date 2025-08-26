#include "stdafx.h"
#include "../Course_work/fraction.h"

TEST(FractionEqualityOperator, ZeroEquality) {
	EXPECT_EQ(Fraction() == Fraction(0, 1), true);
	EXPECT_EQ(Fraction(-0, -1) == Fraction(0, 1), true);
}

TEST(FractionEqualityOperator, NegativeEquality) {
	EXPECT_EQ(Fraction(-3) == Fraction(-3, 1), true);
	EXPECT_EQ(Fraction(1, -5) == Fraction(-1, 5), true);
	EXPECT_EQ(Fraction(1, -5) == Fraction(1, 5), false);
}


TEST(FractionGreaterThanOperator, GreaterThanZero) {
	EXPECT_EQ(Fraction(3) > Fraction(0), true);
	EXPECT_EQ(Fraction(-1) > Fraction(0), false);
	EXPECT_EQ(Fraction(0) > Fraction(0), false);
}

TEST(FractionGreaterThanOperator, GreaterThanFractions) {
	EXPECT_EQ(Fraction(3) > Fraction(1, 5), true);
	EXPECT_EQ(Fraction(3) > Fraction(15, 5), false);
	EXPECT_EQ(Fraction(3) > Fraction(17, 5), false);

	EXPECT_EQ(Fraction(3, 2) > Fraction(3, 3), true);
	EXPECT_EQ(Fraction(3, 4) > Fraction(3, 3), false);
}

TEST(FractionGreaterThanOperator, GreaterThanNegativeFractions) {
	EXPECT_EQ(Fraction(-3) > Fraction(-1, 5), false);
	EXPECT_EQ(Fraction(-3) > Fraction(-15, 5), false);
	EXPECT_EQ(Fraction(-3) > Fraction(-17, 5), true);

	EXPECT_EQ(Fraction(-3, 2) > Fraction(-3, 3), false);
	EXPECT_EQ(Fraction(-3, 4) > Fraction(-3, 3), true);
}


TEST(FractionGreaterThanOrEqualOperator, GreaterThanOrEqualZero) {
	EXPECT_EQ(Fraction(3) >= Fraction(0), true);
	EXPECT_EQ(Fraction(-1) >= Fraction(0), false);
	EXPECT_EQ(Fraction(0) >= Fraction(0), true);
}

TEST(FractionGreaterThanOrEqualOperator, GreaterThanOrEqualFractions) {
	EXPECT_EQ(Fraction(3) >= Fraction(1, 5), true);
	EXPECT_EQ(Fraction(3) >= Fraction(15, 5), true);
	EXPECT_EQ(Fraction(3) >= Fraction(17, 5), false);

	EXPECT_EQ(Fraction(3, 2) >= Fraction(3, 3), true);
	EXPECT_EQ(Fraction(3, 4) >= Fraction(3, 3), false);
}

TEST(FractionGreaterThanOrEqualOperator, GreaterThanOrEqualNegativeFractions) {
	EXPECT_EQ(Fraction(-3) >= Fraction(-1, 5), false);
	EXPECT_EQ(Fraction(-3) >= Fraction(-15, 5), true);
	EXPECT_EQ(Fraction(-3) >= Fraction(-17, 5), true);

	EXPECT_EQ(Fraction(-3, 2) >= Fraction(-3, 3), false);
	EXPECT_EQ(Fraction(-3, 4) >= Fraction(-3, 3), true);
}


TEST(FractionLessThanOperator, LessThanZero) {
	EXPECT_EQ(Fraction(3) < Fraction(0), false);
	EXPECT_EQ(Fraction(-1) < Fraction(0), true);
	EXPECT_EQ(Fraction(0) < Fraction(0), false);
}

TEST(FractionLessThanOperator, LessThanFractions) {
	EXPECT_EQ(Fraction(3) < Fraction(1, 5), false);
	EXPECT_EQ(Fraction(3) < Fraction(15, 5), false);
	EXPECT_EQ(Fraction(3) < Fraction(17, 5), true);

	EXPECT_EQ(Fraction(3, 2) < Fraction(3, 3), false);
	EXPECT_EQ(Fraction(3, 4) < Fraction(3, 3), true);
}

TEST(FractionLessThanOperator, LessThanNegativeFractions) {
	EXPECT_EQ(Fraction(-3) < Fraction(-1, 5), true);
	EXPECT_EQ(Fraction(-3) < Fraction(-15, 5), false);
	EXPECT_EQ(Fraction(-3) < Fraction(-17, 5), false);

	EXPECT_EQ(Fraction(-3, 2) < Fraction(-3, 3), true);
	EXPECT_EQ(Fraction(-3, 4) < Fraction(-3, 3), false);
}


TEST(FractionLessThanOrEqualOperator, LessThanOrEqualZero) {
	EXPECT_EQ(Fraction(3) <= Fraction(0), false);
	EXPECT_EQ(Fraction(-1) <= Fraction(0), true);
	EXPECT_EQ(Fraction(0) <= Fraction(0), true);
}

TEST(FractionLessThanOrEqualOperator, LessThanOrEqualFractions) {
	EXPECT_EQ(Fraction(3) <= Fraction(1, 5), false);
	EXPECT_EQ(Fraction(3) <= Fraction(15, 5), true);
	EXPECT_EQ(Fraction(3) <= Fraction(17, 5), true);

	EXPECT_EQ(Fraction(3, 2) <= Fraction(3, 3), false);
	EXPECT_EQ(Fraction(3, 4) <= Fraction(3, 3), true);
}

TEST(FractionLessThanOrEqualOperator, LessThanOrEqualNegativeFractions) {
	EXPECT_EQ(Fraction(-3) <= Fraction(-1, 5), true);
	EXPECT_EQ(Fraction(-3) <= Fraction(-15, 5), true);
	EXPECT_EQ(Fraction(-3) <= Fraction(-17, 5), false);

	EXPECT_EQ(Fraction(-3, 2) <= Fraction(-3, 3), true);
	EXPECT_EQ(Fraction(-3, 4) <= Fraction(-3, 3), false);
}