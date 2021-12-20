#include "Matrix.h"

namespace Lobaev::Math {

    template <class T>
    Matrix<T>::Matrix(size_t m, size_t n): buffer(m, std::vector<T>(n)) {
        if (m == 0 || n == 0) {
            throw "Cannot initialize matrix.";
        }
    }

    template <class T>
    Matrix<T>::Matrix(const std::vector<std::vector<T>> &vector) {
        if (vector.empty() || vector[0].empty()) {
            throw "Cannot initialize matrix.";
        }

        for (const auto &row : vector) {
            if (row.size() != vector[0].size()) {
                throw "Cannot initialize matrix.";
            }
        }

        buffer = vector;
    }

    template<class T>
    T &Matrix<T>::operator()(size_t i, size_t j) {
        if (i >= rows_count() || j >= columns_count()) {
            throw "";
        }

        return buffer[i][j];
    }

    template<class T>
    const T &Matrix<T>::operator()(size_t i, size_t j) const {
        if (i >= rows_count() || j >= columns_count()) {
            throw "";
        }

        return buffer[i][j];
    }

    template <class T>
    bool Matrix<T>::operator==(const Matrix<T> &other) const {
        if (rows_count() != other.rows_count() || columns_count() != other.columns_count()) {
            return false;
        }

        for (size_t i = 0; i < rows_count(); i++) {
            for (size_t j = 0; j < columns_count(); j++) {
                if ((*this)(i, j) != other(i, j)) {
                    return false;
                }
            }
        }
        return true;
    }

    template <class T>
    bool Matrix<T>::operator!=(const Matrix<T> &other) const {
        return !(*this == other);
    }

    template <class T>
    Vector<T> Matrix<T>::operator*(const Vector<T> &vector) const {
        if (columns_count() != vector.size()) {
            throw "different dimensions";
        }

        Vector<T> result(rows_count());
        for (size_t i = 0; i < rows_count(); i++) {
            for (size_t j = 0; j < columns_count(); j++) {
                result(i) += (*this)(i, j) * vector(j);
            }
        }
        return result;
    }

    template <class T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T> &other) const {
        if (columns_count() != other.rows_count()) {
            throw "different dimensions";
        }

        Matrix<T> result(rows_count(), other.columns_count());
        for (size_t i = 0; i < rows_count(); i++) {
            for (size_t j = 0; j < other.columns_count(); j++) {
                for (size_t k = 0; k < columns_count(); k++) {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    template <class T>
    size_t Matrix<T>::rows_count() const {
        return buffer.size();
    }

    template <class T>
    size_t Matrix<T>::columns_count() const {
        return buffer[0].size();
    }

    template <class T>
    bool Matrix<T>::is_square() const {
        return rows_count() == columns_count();
    }

    template <class T>
    Matrix<T> Matrix<T>::transpose() const {
        Matrix<T> result(columns_count(), rows_count());
        for (size_t i = 0; i < rows_count(); i++) {
            for (size_t j = 0; j < columns_count(); j++) {
                result(j, i) = (*this)(i, j);
            }
        }
        return result;
    }

    template <class T>
    void Matrix<T>::swap_rows(const size_t row_index1, const size_t row_index2) {
        if (row_index1 >= rows_count() || row_index2 >= rows_count()) {
            throw "";
        }

        std::swap(buffer[row_index1], buffer[row_index2]);
    }

    template <class T>
    void Matrix<T>::swap_columns(const size_t column_index1, const size_t column_index2) {
        if (column_index1 >= columns_count() || column_index2 >= columns_count()) {
            throw "";
        }

        for (size_t row_index = 0; row_index < rows_count(); row_index++) {
            std::swap(buffer[row_index][column_index1], buffer[row_index][column_index2]);
        }
    }
    
    template <class T>
    Matrix<T> Matrix<T>::resize(const size_t rows_from, const size_t rows_to,
                                const size_t columns_from, const size_t columns_to) const { //[rows_from; rows_to), ...
        if (rows_from >= rows_to || columns_from >= columns_to) {
            throw "";
        }
        
        Matrix<T> resized_matrix(rows_to - rows_from, columns_to - columns_from);
        if (rows_from < rows_count() && columns_from < columns_count()) {
            const size_t rows_to_ = std::min(rows_to, rows_count());
            const size_t columns_to_ = std::min(columns_to, columns_count());
            
            for (size_t row_index = rows_from; row_index < rows_to_; row_index++) {
                for (size_t column_index = columns_from; column_index < columns_to_; column_index++) {
                    resized_matrix(row_index - rows_from, column_index - columns_from) = (*this)(row_index, column_index);
                }
            }
        }
        return resized_matrix;
    }

    template <class T>
    bool Matrix<T>::is_diagonally_dominant(const size_t index) const {
        T element = (*this)(index, index);
        if (element < 0) {
            element = -element;
        }

        T sum = 0;
        for (size_t index2 = 0; index2 < columns_count() && sum < element; index2++) {
            if (index2 == index) {
                continue;
            }

            T cur_element = (*this)(index, index2);
            if (cur_element < 0) {
                cur_element = -cur_element;
            }

            sum += cur_element;
        }
        return sum < element;
    }

    template <class T>
    bool Matrix<T>::is_diagonally_dominant() const {
        if (!is_square()) {
            return false;
        }

        for (size_t index = 0; index < rows_count(); index++) {
            if (!is_diagonally_dominant(index)) {
                return false;
            }
        }
        return true;
    }

    template <class T>
    template <class T2>
    T2 Matrix<T>::norm(size_t p) const {
        if (!is_square()) {
            throw "";
        }

        T2 sum = (T2) 0;
        for (size_t row_index = 0; row_index < rows_count(); row_index++) {
            for (size_t column_index = 0; column_index < columns_count(); column_index++) {
                sum += (T2) std::pow((T2) (*this)(row_index, column_index), p);
            }
        }

        return (T2) std::pow(sum, (T2) std::pow(p, -1));
    }

    template <class T>
    template <class T2>
    T2 Matrix<T>::norm_euclidean() const {
        return norm<T2>(2);
    }

    template<class T>
    template<class T2>
    T2 Matrix<T>::norm_infinite() const {
        if (!is_square()) {
            throw "";
        }

        T2 best_sum = (T2) (*this)(0, 0);
        for (size_t column_index = 1; column_index < columns_count(); column_index++) {
            best_sum += (T2) (*this)(0, column_index);
        }

        for (size_t row_index = 1; row_index < rows_count(); row_index++) {
            T2 cur_sum = (T2) (*this)(row_index, 0);
            for (size_t column_index = 1; column_index < columns_count(); column_index++) {
                T cur_element = (*this)(row_index, column_index);
                if (cur_element < 0) {
                    cur_element = -cur_element;
                }

                cur_sum += (T2) cur_element;
            }

            if (best_sum < cur_sum) {
                best_sum = cur_sum;
            }
        }

        return best_sum;
    }

}
