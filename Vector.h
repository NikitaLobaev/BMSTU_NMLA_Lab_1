#ifndef NMLA_LAB_1_VECTOR_H
#define NMLA_LAB_1_VECTOR_H


#include <vector>

namespace Lobaev::Math {

    template <class T>
    class Vector {
    private:
        std::vector<T> buffer;
    public:
        explicit Vector(size_t);

        explicit Vector(const std::vector<T>&);

        [[nodiscard]] size_t size() const;

        T &operator()(size_t);

        const T &operator()(size_t) const;

        bool operator==(const Vector<T>&) const;

        bool operator!=(const Vector<T>&) const;

        T operator*(const Vector<T>&) const;

        void swap(size_t, size_t);
    };

}


#endif //NMLA_LAB_1_VECTOR_H
