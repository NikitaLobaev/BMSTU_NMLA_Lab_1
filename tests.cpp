#include "gtest/gtest.h"
#include "Matrix.cpp"

using namespace Lobaev::Math;

TEST(vector, size_ok) {
    const size_t size = 3;
    const Vector<int> vector(size);

    ASSERT_EQ(vector.size(), size);
}

TEST(vector, size_empty_fail) {
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
    Vector<int> vector1({
        1,
        13
    });

    Vector<int> vector2({
        1,
        13
    });

    ASSERT_EQ(vector1, vector2);

    vector1(1) += 1;

    ASSERT_NE(vector1, vector2);
}

TEST(vector, operator_equals_2) {
    const Vector<int> vector1(2);
    const Vector<int> vector2(3);

    ASSERT_NE(vector1, vector2);
}

TEST(vector, multiply_ok) {
    const Vector<int> vector1({
        1,
        2,
        3,
        4,
        5
    });
    const Vector<int> vector2({
        5,
        4,
        3,
        2,
        1
    });

    const int result = vector1 * vector2;

    const int expected_result = vector1(0) * vector2(0) + vector1(1) * vector2(1) +
                                vector1(2) * vector2(2) + vector1(3) * vector2(3) +
                                vector1(4) * vector2(4);

    ASSERT_EQ(result, expected_result);
}

TEST(vector, multiply_fail) {
    const Vector<int> vector1(2), vector2(3);

    ASSERT_ANY_THROW({
        vector1 * vector2;
    });
}

TEST(vector, minus_unary_ok) {
    const Vector<int> vector({
        -1,
        2,
        -3,
        0
    });

    const Vector<int> result = -vector;

    const Vector<int> expected_result({
        1,
        -2,
        3,
        0
    });

    ASSERT_EQ(result, expected_result);
}

TEST(vector, plus_ok) {
    const Vector<int> vector1({
        -1,
        2,
        -3,
        0,
        -11
    });
    const Vector<int> vector2({
        5,
        3,
        -1,
        9,
        0
    });

    const Vector<int> result = vector1 + vector2;

    const Vector<int> expected_result({
        4,
        5,
        -4,
        9,
        -11
    });

    ASSERT_EQ(result, expected_result);
}

TEST(vector, plus_dimensions_fail) {
    const Vector<int> vector1({
        1,
        2
    });
    const Vector<int> vector2({
        3,
        4,
        5
    });

    ASSERT_ANY_THROW({
        vector1 + vector2;
    });
}

TEST(vector, minus_ok) {
    const Vector<int> vector1({
        5,
        2,
        -1,
        9,
        0
    });
    const Vector<int> vector2({
        -1,
        3,
        -3,
        0,
        -11
    });

    const Vector<int> result = vector1 - vector2;

    const Vector<int> expected_result({
        6,
        -1,
        2,
        9,
        11
    });

    ASSERT_EQ(result, expected_result);
}

TEST(vector, minus_dimensions_fail) {
    const Vector<int> vector1({
        3,
        4,
        5
    });
    const Vector<int> vector2({
        1,
        2
    });

    ASSERT_ANY_THROW({
        vector1 - vector2;
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

TEST(vector, norm_ok) {
    const Vector<int> vector({
        -1,
        3,
        -3,
        0,
        -11
    });

    const auto norm_1 = vector.norm<double>(1);

    const double expected_norm_1 = -12;

    ASSERT_EQ(norm_1, std::round(expected_norm_1));
}

TEST(vector, norm_euclidean_ok) {
    const Vector<int> vector({
        -1,
        3,
        -3,
        0,
        -11,
        2
    });

    const auto norm_euclidean = vector.norm_euclidean<double>();

    const double expected_norm_euclidean = 12;

    ASSERT_EQ(norm_euclidean, std::round(expected_norm_euclidean));
}

TEST(vector, norm_infinite_ok) {
    const Vector<int> vector({
        -1,
        3,
        0,
        2,
        -11
    });

    const auto norm_infinite = vector.norm_infinite<double>();

    const double expected_norm_infinite = 3;

    ASSERT_EQ(norm_infinite, std::round(expected_norm_infinite));
}

TEST(matrix, dimensions_ok) {
    const size_t m = 2, n = 3;
    const Matrix<int> matrix(m, n);

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
    Matrix<int> matrix1({
        {1, 2},
        {3, 4}
    });
    Matrix<int> matrix2({
        {1, 2},
        {3, 4}
    });

    ASSERT_EQ(matrix1, matrix2);

    matrix2(0, 0) += 1;

    ASSERT_NE(matrix1, matrix2);
}

TEST(matrix, operator_equals_2) {
    const Matrix<int> matrix1(2, 3), matrix2(3, 2);

    ASSERT_NE(matrix1, matrix2);
}

TEST(matrix, operator_multiply_vector_ok) {
    const Matrix<int> matrix({
        {1, 2, 3},
        {4, 5, 6}
    });
    const Vector<int> vector({
        7,
        8,
        9
    });

    const Vector<int> result = matrix * vector;

    const Vector<int> expected_result({
        50,
        122
    });

    ASSERT_EQ(result, expected_result);
}

TEST(matrix, operator_multiply_vector_fail) {
    const Matrix<int> matrix(2, 3);
    const Vector<int> vector(2);

    ASSERT_ANY_THROW({
        matrix * vector;
    });
}

TEST(matrix, operator_multiply_matrix_ok) {
    const Matrix<int> matrix1({
        {1, 2, 3},
        {4, 5, 6}
    });
    const Matrix<int> matrix2({
        {7, 8},
        {9, 10},
        {11, 12}
    });

    const Matrix<int> result = matrix1 * matrix2;

    const Matrix<int> expected_result({
        {58, 64},
        {139, 154}
    });

    ASSERT_EQ(result, expected_result);
}

TEST(matrix, operator_multiply_matrix_fail) {
    const Matrix<int> matrix1(2, 3), matrix2(2, 3);

    ASSERT_ANY_THROW({
        matrix1 * matrix2;
    });
}

TEST(matrix, is_square_1_ok) {
    const Matrix<int> matrix(2, 2);
    ASSERT_TRUE(matrix.is_square());
}

TEST(matrix, is_square_2_ok) {
    const Matrix<int> matrix(2, 3);
    ASSERT_FALSE(matrix.is_square());
}

TEST(matrix, transpose_ok) {
    const Matrix<int> matrix({
        {1, 2, 3},
        {4, 5, 6}
    });

    const Matrix<int> result_matrix = matrix.transpose();

    const Matrix<int> expected_matrix({
        {1, 4},
        {2, 5},
        {3, 6}
    });

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

TEST(matrix, norm_ok) {
    const Matrix<int> matrix({
        {0, 1, -2},
        {6, -7, 8},
        {3, 4, 5}
    });

    const auto norm = matrix.template norm<int>(1);

    const int expected_norm = 18;

    ASSERT_EQ(norm, expected_norm);
}

TEST(matrix, norm_dimensions_fail) {
    const Matrix<int> matrix({
        {0, 1, 2},
        {3, 4, 5}
    });

    ASSERT_ANY_THROW({
        matrix.template norm<int>(1);
    });
}

TEST(matrix, norm_euclidean_ok) {
    const Matrix<int> matrix({
        {-2, -5, -10},
        {2, 5, -10},
        {2, 4, 10}
    });

    const auto norm = matrix.template norm_euclidean<double>();

    const double expected_norm = std::sqrt(378);

    ASSERT_EQ(std::round(norm), std::round(expected_norm));
}

TEST(matrix, norm_infinite_ok) {
    const Matrix<int> matrix({
        {-2, -5, -10},
        {2, 5, -10},
        {2, 4, 10}
    });

    const auto norm_infinite = matrix.norm_infinite<int>();

    const double expected_norm_infinite = 17;

    ASSERT_EQ(norm_infinite, expected_norm_infinite);
}
