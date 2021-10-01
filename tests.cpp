#include "gtest/gtest.h"
#include "Matrix.cpp"

using namespace Lobaev::Math;

TEST(vector, size_ok) {
    const size_t size = 3;
    Vector<int> vector(size);

    ASSERT_EQ(vector.size(), size);
}

TEST(vector, empty) {
    ASSERT_ANY_THROW({
        Vector<int>(0);
    });
}

TEST(vector, operator_at_ok) {
    Vector<int> vector(4);
    vector(1) = 10;
    vector(3) = 15;

    ASSERT_EQ(vector(0), 0);
    ASSERT_EQ(vector(1), 10);
    ASSERT_EQ(vector(2), 0);
    ASSERT_EQ(vector(3), 15);
}

TEST(vector, operator_at_fail) {
    Vector<int> vector(3);

    ASSERT_ANY_THROW({
        vector(3) = 7;
    });
}

TEST(vector, operator_at_const_ok) {
    Vector<int> vector(4);
    vector(1) = 10;
    vector(3) = 15;

    const Vector<int> &vector_ref = vector;

    ASSERT_EQ(vector_ref(0), 0);
    ASSERT_EQ(vector_ref(1), 10);
    ASSERT_EQ(vector_ref(2), 0);
    ASSERT_EQ(vector_ref(3), 15);
}

TEST(vector, operator_at_const_fail) {
    Vector<int> vector(3);

    const Vector<int> &vector_ref = vector;

    ASSERT_ANY_THROW({
        vector_ref(3);
    });
}

TEST(vector, operator_equals_1) {
    Vector<int> vector1(2);
    vector1(0) = 1;
    vector1(1) = 13;

    Vector<int> vector2(2);
    vector2(0) = 1;
    vector2(1) = 13;

    ASSERT_EQ(vector1, vector2);

    vector1(1) += 1;

    ASSERT_NE(vector1, vector2);
}

TEST(vector, operator_equals_2) {
    Vector<int> vector1(2);
    Vector<int> vector2(3);

    ASSERT_NE(vector1, vector2);
}

TEST(vector, multiply_ok) {
    Vector<int> vector1(5);
    vector1(0) = 1;
    vector1(1) = 2;
    vector1(2) = 3;
    vector1(3) = 4;
    vector1(4) = 5;

    Vector<int> vector2(5);
    vector2(0) = 5;
    vector2(1) = 4;
    vector2(2) = 3;
    vector2(3) = 2;
    vector2(4) = 1;

    const int result = vector1 * vector2;

    const int expected_result = vector1(0) * vector2(0) + vector1(1) * vector2(1) +
                                vector1(2) * vector2(2) + vector1(3) * vector2(3) +
                                vector1(4) * vector2(4);

    ASSERT_EQ(result, expected_result);
}

TEST(vector, multiply_fail) {
    Vector<int> vector1(2), vector2(3);

    ASSERT_ANY_THROW({
        vector1 * vector2;
    });
}

TEST(vector, swap_ok) {
    Vector<int> vector({
        1,
        9,
        4,
        5
    });

    vector.swap(1, 3);

    const Vector<int> expected_result({
        1,
        5,
        4,
        9
    });

    ASSERT_EQ(vector, expected_result);
}

TEST(vector, swap_index1_fail) {
    Vector<int> vector({
        3,
        6,
        9
    });

    ASSERT_ANY_THROW({
        vector.swap(3, 1);
    });
}

TEST(vector, swap_index2_fail) {
    Vector<int> vector({
        3,
        6,
        9
    });

    ASSERT_ANY_THROW({
        vector.swap(1, 3);
    });
}

TEST(matrix, dimensions_ok) {
    const size_t m = 2, n = 3;
    Matrix<int> matrix(m, n);

    ASSERT_EQ(matrix.rows_count(), m);
    ASSERT_EQ(matrix.columns_count(), n);
}

TEST(matrix, dimensions_fail) {
    ASSERT_ANY_THROW({
        Matrix<int>(0, 3);
    });
    ASSERT_ANY_THROW({
        Matrix<int>(10, 0);
    });
}

TEST(matrix, operator_at_ok) {
    Matrix<int> matrix(2, 3);
    matrix(0, 0) = 1;
    matrix(0, 2) = 10;
    matrix(1, 2) = 15;

    ASSERT_EQ(matrix(0, 0), 1);
    ASSERT_EQ(matrix(0, 1), 0);
    ASSERT_EQ(matrix(0, 2), 10);
    ASSERT_EQ(matrix(1, 0), 0);
    ASSERT_EQ(matrix(1, 1), 0);
    ASSERT_EQ(matrix(1, 2), 15);
}

TEST(matrix, operator_at_failed) {
    Matrix<int> matrix(1, 4);

    ASSERT_ANY_THROW({
        matrix(1, 0) = 10;
    });
    ASSERT_ANY_THROW({
        matrix(0, 4) = 15;
    });
}

TEST(matrix, operator_equals_1) {
    Matrix<int> matrix1(2, 2);
    matrix1(0, 0) = 1;
    matrix1(0, 1) = 2;
    matrix1(1, 0) = 3;
    matrix1(1, 1) = 4;

    Matrix<int> matrix2(2, 2);
    matrix2(0, 0) = 1;
    matrix2(0, 1) = 2;
    matrix2(1, 0) = 3;
    matrix2(1, 1) = 4;

    ASSERT_EQ(matrix1, matrix2);

    matrix2(0, 0) += 1;

    ASSERT_NE(matrix1, matrix2);
}

TEST(matrix, operator_equals_2) {
    Matrix<int> matrix1(2, 3), matrix2(3, 2);

    ASSERT_NE(matrix1, matrix2);
}

TEST(matrix, operator_multiply_vector_ok) {
    Matrix<int> matrix(2, 3);
    matrix(0, 0) = 1;
    matrix(0, 1) = 2;
    matrix(0, 2) = 3;
    matrix(1, 0) = 4;
    matrix(1, 1) = 5;
    matrix(1, 2) = 6;

    Vector<int> vector(3);
    vector(0) = 7;
    vector(1) = 8;
    vector(2) = 9;

    Vector<int> result = matrix * vector;

    Vector<int> expected_result(2);
    expected_result(0) = 50;
    expected_result(1) = 122;

    ASSERT_EQ(result, expected_result);
}

TEST(matrix, operator_multiply_vector_fail) {
    Matrix<int> matrix(2, 3);
    Vector<int> vector(2);

    ASSERT_ANY_THROW({
        matrix * vector;
    });
}

TEST(matrix, operator_multiply_matrix_ok) {
    Matrix<int> matrix1(2, 3);
    matrix1(0, 0) = 1;
    matrix1(0, 1) = 2;
    matrix1(0, 2) = 3;
    matrix1(1, 0) = 4;
    matrix1(1, 1) = 5;
    matrix1(1, 2) = 6;

    Matrix<int> matrix2(3, 2);
    matrix2(0, 0) = 7;
    matrix2(0, 1) = 8;
    matrix2(1, 0) = 9;
    matrix2(1, 1) = 10;
    matrix2(2, 0) = 11;
    matrix2(2, 1) = 12;

    Matrix<int> result = matrix1 * matrix2;

    Matrix<int> expected_result(2, 2);
    expected_result(0, 0) = 58;
    expected_result(0, 1) = 64;
    expected_result(1, 0) = 139;
    expected_result(1, 1) = 154;

    ASSERT_EQ(result, expected_result);
}

TEST(matrix, operator_multiply_matrix_fail) {
    Matrix<int> matrix1(2, 3), matrix2(2, 3);

    ASSERT_ANY_THROW({
        matrix1 * matrix2;
    });
}

TEST(matrix, is_square_1_ok) {
    Matrix<int> matrix(2, 2);
    ASSERT_TRUE(matrix.is_square());
}

TEST(matrix, is_square_2_ok) {
    Matrix<int> matrix(2, 3);
    ASSERT_FALSE(matrix.is_square());
}

TEST(matrix, transpose_ok) {
    Matrix<int> matrix(2, 3);
    matrix(0, 0) = 1;
    matrix(0, 1) = 2;
    matrix(0, 2) = 3;
    matrix(1, 0) = 4;
    matrix(1, 1) = 5;
    matrix(1, 2) = 6;

    Matrix<int> result_matrix = matrix.transpose();

    Matrix<int> expected_matrix(3, 2);
    expected_matrix(0, 0) = 1;
    expected_matrix(0, 1) = 4;
    expected_matrix(1, 0) = 2;
    expected_matrix(1, 1) = 5;
    expected_matrix(2, 0) = 3;
    expected_matrix(2, 1) = 6;

    ASSERT_EQ(result_matrix, expected_matrix);
}

TEST(matrix, swap_rows_ok) {
    Matrix<int> matrix({
        {1, 2},
        {3, 4},
        {5, 6}
    });

    matrix.swap_rows(0, 2);

    const Matrix<int> expected_result({
        {5, 6},
        {3, 4},
        {1, 2}
    });

    ASSERT_EQ(matrix, expected_result);
}

TEST(matrix, swap_rows_fail_index1) {
    Matrix<int> matrix({
        {1, 2},
        {3, 4},
        {5, 6}
    });

    ASSERT_ANY_THROW({
        matrix.swap_rows(3, 1);
    });
}

TEST(matrix, swap_rows_fail_index2) {
    Matrix<int> matrix({
        {1, 2},
        {3, 4},
        {5, 6}
    });

    ASSERT_ANY_THROW({
        matrix.swap_rows(1, 3);
    });
}

TEST(matrix, swap_columns_ok) {
    Matrix<int> matrix({
        {1, 2, 3},
        {4, 5, 6}
    });

    matrix.swap_columns(0, 2);

    const Matrix<int> expected_result({
        {3, 2, 1},
        {6, 5, 4}
    });

    ASSERT_EQ(matrix, expected_result);
}

TEST(matrix, swap_columns_fail_index1) {
    Matrix<int> matrix({
        {1, 2, 3},
        {4, 5, 6}
    });

    ASSERT_ANY_THROW({
        matrix.swap_columns(3, 1);
    });
}

TEST(matrix, swap_columns_fail_index2) {
    Matrix<int> matrix({
        {1, 2, 3},
        {4, 5, 6}
    });

    ASSERT_ANY_THROW({
        matrix.swap_columns(1, 3);
    });
}

TEST(matrix, is_diagonally_dominant_1_ok) {
    const Matrix<int> matrix({
        {5, 2, 1},
        {4, 9, 3},
        {5, 0, 6}
    });

    ASSERT_TRUE(matrix.is_diagonally_dominant());
}

TEST(matrix, is_diagonally_dominant_2_ok) {
    const Matrix<int> matrix({
        {19, -3, 2, 5, 3},
        {11, -13, 0, 1, 0},
        {0, 0, -11, -10, 0},
        {4, 3, 0, 9, 1},
        {-3, -2, -5, -1, -14}
    });

    ASSERT_TRUE(matrix.is_diagonally_dominant());
}

TEST(matrix, is_diagonally_dominant_3_fail) {
    const Matrix<int> matrix({
        {4, 1, 0},
        {2, 5, 1}
    });

    ASSERT_FALSE(matrix.is_diagonally_dominant());
}

TEST(matrix, is_diagonally_dominant_4_fail) {
    const Matrix<int> matrix({
        {2, 1},
        {3, 3}
    });

    ASSERT_FALSE(matrix.is_diagonally_dominant());
}

TEST(matrix, is_diagonally_dominant_5_fail) {
    const Matrix<int> matrix({
        {-5, 1, -2},
        {-3, -1, 0},
        {1, 2, 5}
    });

    ASSERT_FALSE(matrix.is_diagonally_dominant());
}
