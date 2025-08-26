#include "stdafx.h"
#include "../Course_work/fraction.h"

TEST(FractionTest, BooleanNegationOperator) {
	Fraction f1 = -Fraction(2, 5);
	EXPECT_EQ(f1.n, -2);
	EXPECT_EQ(f1.d, 5);

	Fraction f2 = -Fraction(0, 5);
	EXPECT_EQ(f2.n, 0);
	EXPECT_EQ(f2.d, 1);

	Fraction f3 = -Fraction(3, -5);
	EXPECT_EQ(f3.n, 3);
	EXPECT_EQ(f3.d, 5);

	Fraction f4 = -Fraction(-3, 5);
	EXPECT_EQ(f4.n, 3);
	EXPECT_EQ(f4.d, 5);
}

TEST(FractionTest, SubstractionOperator) {
	Fraction f1 = Fraction(2, 5) - Fraction(2, 5);
	EXPECT_EQ(f1.n, 0);
	EXPECT_EQ(f1.d, 1);

	Fraction f2 = Fraction(2, 5) - Fraction(3, 5);
	EXPECT_EQ(f2.n, -1);
	EXPECT_EQ(f2.d, 5);

	Fraction f3 = Fraction(3, 5) - Fraction(2, 5);
	EXPECT_EQ(f3.n, 1);
	EXPECT_EQ(f3.d, 5);

	Fraction f4 = Fraction(15, 8) - Fraction(3, 4);
	EXPECT_EQ(f4.n, 9);
	EXPECT_EQ(f4.d, 8);

	Fraction f5 = Fraction(33, 9) - Fraction(2, 3);
	EXPECT_EQ(f5.n, 3);
	EXPECT_EQ(f5.d, 1);

	Fraction f6 = Fraction(2, 9) - Fraction(0);
	EXPECT_EQ(f6.n, 2);
	EXPECT_EQ(f6.d, 9);
}

TEST(FractionTest, AdditionOperator) {
	Fraction f1 = Fraction(2, 5) + Fraction(2, 5);
	EXPECT_EQ(f1.n, 4);
	EXPECT_EQ(f1.d, 5);

	Fraction f2 = Fraction(2, 5) + Fraction(3, 5);
	EXPECT_EQ(f2.n, 1);
	EXPECT_EQ(f2.d, 1);

	Fraction f3 = Fraction(-3, 5) + Fraction(2, 5);
	EXPECT_EQ(f3.n, -1);
	EXPECT_EQ(f3.d, 5);

	Fraction f4 = Fraction(3, -5) + Fraction(2, 5);
	EXPECT_EQ(f4.n, -1);
	EXPECT_EQ(f4.d, 5);

	Fraction f5 = Fraction(-3, 5) + Fraction(4, 5);
	EXPECT_EQ(f5.n, 1);
	EXPECT_EQ(f5.d, 5);

	Fraction f6 = Fraction(33, 9) + Fraction(0);
	EXPECT_EQ(f6.n, 11);
	EXPECT_EQ(f6.d, 3);
}

TEST(FractionTest, MultipleOperator) {
	Fraction f1 = Fraction(2, 5) * Fraction(2, 5);
	EXPECT_EQ(f1.n, 4);
	EXPECT_EQ(f1.d, 25);

	Fraction f3 = Fraction(-3, 5) * Fraction(2, 5);
	EXPECT_EQ(f3.n, -6);
	EXPECT_EQ(f3.d, 25);

	Fraction f4 = Fraction(3, -5) * Fraction(2, 5);
	EXPECT_EQ(f4.n, -6);
	EXPECT_EQ(f4.d, 25);

	Fraction f5 = Fraction(3, -5) * Fraction(-2, 5);
	EXPECT_EQ(f5.n, 6);
	EXPECT_EQ(f5.d, 25);

	Fraction f6 = Fraction(33, 9) * Fraction(0);
	EXPECT_EQ(f6.n, 0);
	EXPECT_EQ(f6.d, 1);

	Fraction f7 = Fraction(-33, 9) * Fraction(0);
	EXPECT_EQ(f7.n, 0);
	EXPECT_EQ(f7.d, 1);
}

TEST(FractionTest, DivisionOperator) {
	Fraction f1 = Fraction(2, 5) / Fraction(2, 5);
	EXPECT_EQ(f1.n, 1);
	EXPECT_EQ(f1.d, 1);

	Fraction f3 = Fraction(-2, 5) / Fraction(2, 5);
	EXPECT_EQ(f3.n, -1);
	EXPECT_EQ(f3.d, 1);

	Fraction f4 = Fraction(2, -5) / Fraction(2, 5);
	EXPECT_EQ(f4.n, -1);
	EXPECT_EQ(f4.d, 1);

	Fraction f5 = Fraction(-5) / Fraction(-1, 2);
	EXPECT_EQ(f5.n, 5);
	EXPECT_EQ(f5.d, 2);

	Fraction f6 = Fraction(0) / Fraction(3, 5);
	EXPECT_EQ(f6.n, 0);
	EXPECT_EQ(f6.d, 1);
}