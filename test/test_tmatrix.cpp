#include "utmatrix.h"

#include <gtest.h>

TEST(TMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix)
{
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one)
{
	TMatrix<int> A1(5);
	TMatrix<int> A2(A1);
	EXPECT_EQ(A1, A2);
}

TEST(TMatrix, copied_matrix_has_its_own_memory)
{
	TMatrix<int> A1(5);
	TMatrix<int> A2(A1);
	EXPECT_NE(A1.GetVector(), A2.GetVector());
}


TEST(TMatrix, can_get_size)
{
	TMatrix<int>A(8);
	EXPECT_EQ(A.GetSize(), 8);
}

TEST(TMatrix, can_set_and_get_element)
{
	TMatrix<int>A(8);
	A[1][2] = 9;
	EXPECT_EQ(A[1][2], 9);
}

TEST(TMatrix, throws_when_set_element_with_negative_index)
{
	TMatrix<int>A(3);
	ASSERT_ANY_THROW(A[-1][-2]);
}

TEST(TMatrix, throws_when_set_element_with_too_large_index)
{
	TMatrix<int>A(3);
	ASSERT_ANY_THROW(A[5][5]);
}

TEST(TMatrix, can_assign_matrix_to_itself)
{
	TMatrix<int>A(3);
	ASSERT_NO_THROW(A = A);

}

TEST(TMatrix, can_assign_matrices_of_equal_size)
{
	TMatrix<int>A1(3);
	TMatrix<int>A2(3);
	auto i = A2.GetVector();
	A2 = A1;
	EXPECT_EQ(i, A2.GetVector());

}

TEST(TMatrix, assign_operator_change_matrix_size)
{
	TMatrix<int>A1(3);
	TMatrix<int>A2(4);
	auto i = A2.GetVector();
	A2 = A1;
	EXPECT_EQ(A2.GetSize(), 3);
}

TEST(TMatrix, can_assign_matrices_of_different_size)
{
	TMatrix<int>A1(3);
	TMatrix<int>A2(4);
	ASSERT_NO_THROW(A2 = A1);
}

TEST(TMatrix, compare_equal_matrices_return_true)
{
	TMatrix<int>A1(10);
	TMatrix<int>A2(10);
	EXPECT_EQ(A1, A2);
}

TEST(TMatrix, compare_matrix_with_itself_return_true)
{
	TMatrix<int>A1(10);
	EXPECT_EQ(A1, A1);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal)
{
	TMatrix<int>A1(10);
	TMatrix<int>A2(11);
	EXPECT_NE(A1, A2);
}

TEST(TMatrix, can_add_matrices_with_equal_size)
{
	TMatrix<int>A1(10);
	TMatrix<int>A2(10);
	ASSERT_NO_THROW(A1 + A2);
}

TEST(TMatrix, cant_add_matrices_with_not_equal_size)
{
	TMatrix<int>A1(10);
	TMatrix<int>A2(12);
	ASSERT_ANY_THROW(A1 + A2);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size)
{
	TMatrix<int>A1(10);
	TMatrix<int>A2(10);
	ASSERT_NO_THROW(A1 - A2);
}

TEST(TMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TMatrix<int>A1(10);
	TMatrix<int>A2(12);
	ASSERT_ANY_THROW(A1 - A2);
}
