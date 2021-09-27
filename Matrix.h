#ifndef NMLA_LAB_1_MATRIX_H
#define NMLA_LAB_1_MATRIX_H

#include "Vector.cpp"

namespace Lobaev::Math {

    template <class T>
    class Matrix {
    private:
        std::vector<std::vector<T>> buffer;
    public:
        Matrix(size_t, size_t);

        Matrix(const std::vector<std::vector<T>>&);

        T &operator()(size_t, size_t);

        const T &operator()(size_t, size_t) const;

        bool operator==(const Matrix<T>&) const;

        bool operator!=(const Matrix<T>&) const;

        Vector<T> operator*(const Vector<T>&) const;

        Matrix<T> operator*(const Matrix<T>&) const;

        [[nodiscard]] size_t rows_count() const;

        [[nodiscard]] size_t columns_count() const;

        [[nodiscard]] bool is_square() const;

        Matrix<T> transpose() const;

        void swap_rows(size_t, size_t);

        void swap_columns(size_t, size_t);
    };

}


#endif //NMLA_LAB_1_MATRIX_H
