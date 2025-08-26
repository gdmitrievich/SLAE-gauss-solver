#include "stdafx.h"
#include "../Course_work/fraction.h"

TEST(FractionAssignmentOperator, ZeroAssignment) {
	Fraction f = Fraction();
	EXPECT_EQ(f.n, 0);
	EXPECT_EQ(f.d, 1);
}

TEST(FractionAssignmentOperator, HalfAssignment) {
	Fraction f = Fraction(1, 2);
	EXPECT_EQ(f.n, 1);
	EXPECT_EQ(f.d, 2);
}

TEST(FractionAssignmentOperator, NegativeAssignment) {
	Fraction f1 = Fraction(-3);
	EXPECT_EQ(f1.n, -3);
	EXPECT_EQ(f1.d, 1);

	Fraction f2 = Fraction(3, -5);
	EXPECT_EQ(f2.n, -3);
	EXPECT_EQ(f2.d, 5);

	Fraction f3 = Fraction(-1, 5);
	EXPECT_EQ(f3.n, -1);
	EXPECT_EQ(f3.d, 5);

	Fraction f4 = Fraction(-1, -5);
	EXPECT_EQ(f4.n, 1);
	EXPECT_EQ(f4.d, 5);
}