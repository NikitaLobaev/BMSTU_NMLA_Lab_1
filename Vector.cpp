#include <cmath>
#include "Vector.h"

namespace Lobaev::Math {

    template <class T>
    Vector<T>::Vector(size_t size): buffer(size) {
        if (size == 0) {
            throw "size == 0";
        }
    }

    template <class T>
    Vector<T>::Vector(const std::vector<T> &vector) {
        if (vector.empty()) {
            throw "size == 0";
        }

        buffer = vector;
    }

    template <class T>
    size_t Vector<T>::size() const {
        return buffer.size();
    }

    template <class T>
    bool Vector<T>::operator==(const Vector<T> &other) const {
        if (size() != other.size()) {
            return false;
        }

        for (size_t index = 0; index < size(); index++) {
            if ((*this)(index) != other(index)) {
                return false;
            }
        }
        return true;
    }

    template <class T>
    bool Vector<T>::operator!=(const Vector<T> &other) const {
        return !(*this == other);
    }

    template <class T>
    T Vector<T>::operator*(const Vector<T> &other) const {
        if (size() != other.size()) {
            throw "different dimensions";
        }

        T result = other(0) * (*this)(0);
        for (size_t i = 1; i < size(); i++) {
            result += (*this)(i) * other(i);
        }
        return result;
    }

    template<class T>
    T &Vector<T>::operator()(const size_t i) {
        if (i >= size()) {
            throw "";
        }

        return buffer[i];
    }

    template<class T>
    const T &Vector<T>::operator()(const size_t i) const {
        if (i >= size()) {
            throw "";
        }

        return buffer[i];
    }

    template<class T>
    void Vector<T>::swap(const size_t index1, const size_t index2) {
        if (index1 >= size() || index2 >= size()) {
            throw "";
        }

        std::swap(buffer[index1], buffer[index2]);
    }

    template<class T>
    Vector<T> Vector<T>::operator-() const {
        Vector<T> new_vector(*this);
        for (size_t index = 0; index < size(); index++) {
            new_vector(index) = -new_vector(index);
        }
        return new_vector;
    }

    template <class T>
    Vector<T> Vector<T>::operator+(const Vector<T> &other) const {
        if (size() != other.size()) {
            throw "";
        }

        Vector<T> new_vector(*this);
        for (size_t index = 0; index < size(); index++) {
            new_vector(index) += other(index);
        }
        return new_vector;
    }

    template<class T>
    Vector<T> Vector<T>::operator-(const Vector<T> &other) const {
        return *this + -other;
    }

    /**
     * @tparam T
     * @tparam T2 type of returning value, necessary for accounting of the inaccuracy
     * @param p order of the norm (0 - infinite norm)
     * @return p-norm of this vector
     */
    template <class T>
    template <class T2>
    T2 Vector<T>::norm(size_t p) const {
        if (p == 0) {
            size_t index_max = 0;

            for (size_t index = 1; index < size(); index++) {
                if ((*this)(index_max) < (*this)(index)) {
                    index_max = index;
                }
            }

            return (T2) (*this)(index_max);
        }

        T2 sum = (T2) std::pow((T2) (*this)(0), p); //TODO: возможно, из-за std::pow нельзя будет поддержать кастомные типы T, кроме встроенных

        for (size_t index = 1; index < size(); index++) {
            sum += (T2) std::pow((T2) (*this)(index), p);
        }

        return (T2) std::pow(sum, (T2) std::pow(p, -1));
    }

    template <class T>
    template <class T2>
    T2 Vector<T>::norm_euclidean() const {
        return norm<T2>(2);
    }

    template<class T>
    template<class T2>
    T2 Vector<T>::norm_infinite() const {
        return norm<T2>(0);
    }

}
