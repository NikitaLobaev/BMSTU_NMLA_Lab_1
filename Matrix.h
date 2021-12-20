#ifndef NMLA_LAB_1_MATRIX_H
#define NMLA_LAB_1_MATRIX_H

#include "Vector.cpp"

namespace Lobaev::Math {

    template <class T>
    class Matrix {
    private:
        std::vector<std::vector<T>> buffer;

        bool is_diagonally_dominant(size_t) const;
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

        Matrix<T> resize(size_t, size_t, size_t, size_t) const;

        [[nodiscard]] bool is_diagonally_dominant() const;

        template <class T2>
        T2 norm(size_t) const;

        template <class T2>
        T2 norm_euclidean() const;

        template <class T2>
        T2 norm_infinite() const;
    };

}


#endif //NMLA_LAB_1_MATRIX_H
