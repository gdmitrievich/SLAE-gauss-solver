#include "stdafx.h"
#include "../Course_work/fraction.h"

TEST(FractionCtor, DefaultCtor) {
	Fraction f;
	EXPECT_EQ(f.n, 0);
	EXPECT_EQ(f.d, 1);
}

TEST(FractionCtor, OneParamCtor) {
	Fraction f(5);
	EXPECT_EQ(f.n, 5);
	EXPECT_EQ(f.d, 1);
}

TEST(FractionCtor, TwoParamCtorCorrectFractions) {
	Fraction f1(5, 3);
	EXPECT_EQ(f1.n, 5);
	EXPECT_EQ(f1.d, 3);

	Fraction f2(2, -7);
	EXPECT_EQ(f2.n, -2);
	EXPECT_EQ(f2.d, 7);
}

TEST(FractionCtor, TwoParamCtorZeroNumerator) {
	Fraction f1(0, -10);
	EXPECT_EQ(f1.n, 0);
	EXPECT_EQ(f1.d, 1);

	Fraction f2(0, 5);
	EXPECT_EQ(f2.n, 0);
	EXPECT_EQ(f2.d, 1);

	Fraction f3(-0, 5);
	EXPECT_EQ(f3.n, 0);
	EXPECT_EQ(f3.d, 1);
}

TEST(FractionCtor, TwoParamCtorShrinkedFractions) {
	Fraction f1(15, 25);
	EXPECT_EQ(f1.n, 3);
	EXPECT_EQ(f1.d, 5);

	Fraction f2(-30, 18);
	EXPECT_EQ(f2.n, -5);
	EXPECT_EQ(f2.d, 3);
}

TEST(FractionCtor, TwoParamCtorNegativeFractions) {
	Fraction f1(-10, -15);
	EXPECT_EQ(f1.n, 2);
	EXPECT_EQ(f1.d, 3);

	Fraction f2(-30, 18);
	EXPECT_EQ(f2.n, -5);
	EXPECT_EQ(f2.d, 3);

	Fraction f3(5, -3);
	EXPECT_EQ(f3.n, -5);
	EXPECT_EQ(f3.d, 3);

	Fraction f4(25, -30);
	EXPECT_EQ(f4.n, -5);
	EXPECT_EQ(f4.d, 6);
}