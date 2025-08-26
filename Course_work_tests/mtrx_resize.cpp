#include "stdafx.h"
#include "../Course_work/matrix.h"

TEST(MatrixResize, OneValue) {
	Matrix<int> a(1);
	a(1, 1) = 5;

	a.resize(3, 2);
	EXPECT_EQ(a.getRows(), 3);
	EXPECT_EQ(a.getCols(), 2);
	EXPECT_EQ(a(1, 1), 5);
	EXPECT_EQ(a(1, 2), 0);
}

TEST(MatrixResize, MoreThanOneValue) {
	Matrix<int> a(2, 3);
	std::size_t rows = a.getRows();
	std::size_t cols = a.getCols();

	std::size_t n = 1;
	for (std::size_t i = 1, j; i <= rows; ++i)
		for (j = 1; j <= cols; ++j)
			a(i, j) = int (n++);
	a.resize(3, 2);

	EXPECT_EQ(a(1, 1), 1);
	EXPECT_EQ(a(1, 2), 2);
	EXPECT_EQ(a(2, 1), 4);
	EXPECT_EQ(a(2, 2), 5);
	EXPECT_EQ(a(3, 1), 0);
	EXPECT_EQ(a(3, 2), 0);
	
	EXPECT_EQ(a.getRows(), 3);
	EXPECT_EQ(a.getCols(), 2);

	Matrix<int> b(4, 4);
	rows = b.getRows();
	cols = b.getCols();

	n = 1;
	for (std::size_t i = 1, j; i <= rows; ++i)
		for (j = 1; j <= cols; ++j)
			b(i, j) = int (n++);

	b.resize(3, 2);

	EXPECT_EQ(b(1, 1), 1);
	EXPECT_EQ(b(1, 2), 2);
	EXPECT_EQ(b(2, 1), 5);
	EXPECT_EQ(b(2, 2), 6);
	EXPECT_EQ(b(3, 1), 9);
	EXPECT_EQ(b(3, 2), 10);

	EXPECT_EQ(b.getRows(), 3);
	EXPECT_EQ(b.getCols(), 2);

	Matrix<int> c(2, 2);
	rows = c.getRows();
	cols = c.getCols();

	n = 1;
	for (std::size_t i = 1, j; i <= rows; ++i)
		for (j = 1; j <= cols; ++j)
			c(i, j) = int(n++);

	c.resize(3, 3);

	EXPECT_EQ(c(1, 1), 1);
	EXPECT_EQ(c(1, 2), 2);
	EXPECT_EQ(c(1, 3), 0);
	EXPECT_EQ(c(2, 1), 3);
	EXPECT_EQ(c(2, 2), 4);
	EXPECT_EQ(c(2, 3), 0);
	EXPECT_EQ(c(3, 1), 0);
	EXPECT_EQ(c(3, 2), 0);
	EXPECT_EQ(c(3, 3), 0);

	EXPECT_EQ(c.getRows(), 3);
	EXPECT_EQ(c.getCols(), 3);
}