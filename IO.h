#ifndef NMLA_LAB_1_IO_H
#define NMLA_LAB_1_IO_H


#include "Matrix.h"

namespace Lobaev::IO {

    using namespace Lobaev::Math;

    template <class T>
    static Vector<T> read_vector(std::istream&);

    template <class T>
    static Matrix<T> read_matrix(std::istream&);

    template <class T>
    static void print(std::ostream&, const T&);

    template <class T>
    static void print_vector(std::ostream&, const Vector<T>&);

    template <class T>
    static void print_matrix(std::ostream&, const Matrix<T>&);

}


#endif //NMLA_LAB_1_IO_H
