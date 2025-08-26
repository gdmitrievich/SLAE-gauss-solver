#include "stdafx.h"
#include "../Course_work/matrix.h"

TEST(MatrixFuncOperator, DefaulFilling) {
	Matrix<int> m(3, 3);
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			m(i, j) = j;
		}
	}

	EXPECT_EQ(m(1, 1), 1);
	EXPECT_EQ(m(1, 2), 2);
	EXPECT_EQ(m(3, 3), 3);
	EXPECT_EQ(m(2, 3), 3);
	EXPECT_EQ(m(1, 3), 3);
	EXPECT_EQ(m(2, 2), 2);
}

TEST(MatrixFuncOperator, RandomFilling) {
	Matrix<int> m(3, 3);
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			m(i, j) = j;
		}
	}

	EXPECT_EQ(m(1, 1), 1);
	m(1, 1) = 5;
	EXPECT_EQ(m(1, 1), 5);

	EXPECT_EQ(m(3, 3), 3);
	m(3, 3) = 7;
	EXPECT_EQ(m(3, 3), 7);
}