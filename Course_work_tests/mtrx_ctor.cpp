#include "stdafx.h"
#include "../Course_work/matrix.h"

TEST(MatrixCtors, DefaultCtor) {
	Matrix<int> a;
	EXPECT_EQ(a.getCols(), 0);
	EXPECT_EQ(a.getRows(), 0);
}

TEST(MatrixCtors, CtorWithOneParam) {
	Matrix<int> m(4);
	EXPECT_EQ(m.getRows(), 4);
	EXPECT_EQ(m.getCols(), 1);
}

TEST(MatrixCtors, CtorWithTwoParams) {
	Matrix<int> m(4, 2);
	EXPECT_EQ(m.getRows(), 4);
	EXPECT_EQ(m.getCols(), 2);
}

TEST(MatrixCtors, CopyCtor) {
	Matrix<int> m(1, 2);
	Matrix<int> m2(m);

	EXPECT_EQ(m2.getRows(), 1);
	EXPECT_EQ(m2.getCols(), 2);
}