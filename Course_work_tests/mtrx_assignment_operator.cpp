#include "pch.h"
#include "../Course_work/matrix.h"

TEST(MatrixAssignmentOperator, DefaultCtor) {
	Matrix<int> a;
	EXPECT_EQ(a.getCols(), 0);
	EXPECT_EQ(a.getRows(), 0);
}