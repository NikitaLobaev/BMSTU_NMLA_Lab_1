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

}
