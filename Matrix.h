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

        [[nodiscard]] size_t rows_count() const;

        [[nodiscard]] size_t columns_count() const;

        T &operator()(size_t, size_t);

        const T &operator()(size_t, size_t) const;

        bool operator==(const Matrix<T>&) const;

        bool operator!=(const Matrix<T>&) const;

        Vector<T> operator*(const Vector<T>&) const;

        Matrix<T> operator*(const Matrix<T>&) const;

        Matrix<T> transpose() const;
    };

}


#endif //NMLA_LAB_1_MATRIX_H
