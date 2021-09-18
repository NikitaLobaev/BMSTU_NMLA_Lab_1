#include <fstream>
#include "IO.h"

namespace Lobaev::IO {

    using namespace Lobaev::Math;

    template <class T>
    static Vector<T> read_vector(std::ifstream &input) {
        size_t size;
        input >> size;

        Vector<T> vector(size);
        for (size_t i = 0; i < size; i++) {
            input >> vector(i);
        }

        return vector;
    }

    template <class T>
    static Matrix<T> read_matrix(std::ifstream &input) {
        size_t m, n;
        input >> m >> n;

        Matrix<T> matrix(m, n);
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < n; j++) {
                input >> matrix(i, j);
            }
        }

        return matrix;
    }

    template <class T>
    static void print(std::ofstream &output, const T &t) {
        output << t << std::endl;
    }

    template <class T>
    static void print_vector(std::ofstream &output, const Vector<T> &vector) {
        output << vector.size() << std::endl << vector(0);
        for (size_t i = 1; i < vector.size(); i++) {
            output << ' ' << vector(i);
        }
        output << std::endl;
    }

    template <class T>
    static void print_matrix(std::ofstream &output, const Matrix<T> &matrix) {
        output << matrix.rows_count() << ' ' << matrix.columns_count() << std::endl;
        for (size_t i = 0; i < matrix.rows_count(); i++) {
            output << matrix(i, 0);
            for (size_t j = 1; j < matrix.columns_count(); j++) {
                output << ' ' << matrix(i, j);
            }
            output << std::endl;
        }
    }

}
