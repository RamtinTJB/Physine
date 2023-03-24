#ifndef PHYSINE_VECTOR_H_
#define PHYSINE_VECTOR_H_

#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <type_traits>
#include <string>
#include <iostream>

#include "constants.h"

template <class T, size_t N>
class Vector {
    static_assert(std::is_arithmetic<T>::value, "Vector requires an arithmetic data type");
    private:
        T* vector_ = new T[N];

    public:
        typedef T value_type;
        using iterator = T*;
        using const_iterator = T const*;

        constexpr size_t dimension() const noexcept { return N; }

        const_iterator begin() const { return vector_; }
        const_iterator end() const { return vector_ + N; }

        constexpr T& at(size_t index) const {
            if (index >= N || index < 0) throw std::out_of_range("Index out of bounds");
            return vector_[index];
        }

        constexpr T x() const { return vector_[0]; }
        constexpr T y() const { return vector_[1]; }
        constexpr T z() const { return vector_[2]; }

        constexpr T& operator[](size_t index) const {
            return at(index);
        } 

        constexpr double magnitude() const noexcept {
            if (N == 0) return 0;
            double sum_squares = 0;
            for (int i = 0; i < N; ++i) {
                sum_squares += vector_[i] * vector_[i];
            }
            return std::sqrt(sum_squares);
        }

        constexpr double size() const noexcept { return magnitude(); }

        constexpr double dot(const Vector<T, N>& other) const {
            if (N == 0) return 0;
            double result = 0;
            for (int i = 0; i < N; ++i) {
                result += vector_[i] * other.vector_[i];
            }
            return result;
        }

        constexpr Vector<T, 3> cross(const Vector<T, 3>& other) const {
            T _x = y()*other.z() - other.y()*z();
            T _y = z()*other.x() - other.z()*x();
            T _z = x()*other.y() - other.x()*y();
            return Vector{_x, _y, _z};
        }

        constexpr Vector<T, N> add(const Vector<T, N>&other) const {
            Vector<T, N> new_vector;
            for (int i = 0; i < N; ++i) {
                new_vector.vector_[i] = vector_[i] + other.vector_[i];
            }
            return new_vector;
        }

        constexpr Vector<T, N> scalar_multiply(const T& scalar) const {
            Vector<T, N> new_vector;
            for (int i = 0; i < N; ++i) {
                new_vector.vector_[i] = vector_[i] * scalar;
            }
            return new_vector;
        }

        constexpr Vector<T, N> opposite() const {
            return scalar_multiply(-1);
        }

        constexpr Vector<T, N> unit() const {
            return scalar_multiply(1.0/magnitude());
        }

        constexpr T distance(const Vector<T, N>& other) const {
            return std::sqrt((x()-other.x())*(x()-other.x())+(y()-other.y())*(y()-other.y()));
        }

        constexpr Vector<T, N> projection_unto(const Vector<T, N>& other) const {
            return other.scalar_multiply((dot(other))/(other.dot(other)));
        }

        constexpr Vector() {
            for (int i = 0; i < N; ++i) {
                vector_[i] = 0;
            }
        }

        constexpr explicit Vector(std::initializer_list<T> list) {
            if (list.size() != N) {
                throw std::invalid_argument("Number of elements in the initializer list doesn't match the dimension of the vector.");
            }
            std::copy(list.begin(), list.end(), vector_);
        }

        constexpr Vector(const Vector<T, N>& other) {
            std::copy(other.vector_, other.vector_ + N, vector_);
        }

        ~Vector() {
            delete[] vector_;
        }

        constexpr void operator=(const Vector<T, N>& other) {
            std::copy(other.vector_, other.vector_ + N, vector_);
        }

        constexpr Vector<T, N> operator+=(const Vector<T, N>& rhs) const {
            for (int i = 0; i < N; i++) {
                vector_[i] += rhs[i];
            }
            return *this;
        }

        constexpr Vector<T, N> operator-=(const Vector<T, N>& rhs) const {
            for (int i = 0; i < N; i++) {
                vector_[i] -= rhs[i];
            }
            return *this;
        }

        constexpr Vector<T, N> operator-() const {
            return opposite();
        }
};

template <class T, size_t N1, size_t N2>
inline bool operator==(const Vector<T, N1>& lhs, const Vector<T, N2>& rhs) {
    if (lhs.dimension() != rhs.dimension()) return false;
    for (int i = 0; i < lhs.dimension(); ++i) {
        if constexpr (std::is_integral_v<T>) {
            if (lhs.at(i) != rhs.at(i)) return false;
        } else if (std::is_floating_point_v<T>) {
            if (std::abs(lhs.at(i) - rhs.at(i)) > EPSILON) return false;
        }
    }
    return true;
}

template <class T, size_t N1, size_t N2>
inline bool operator!=(const Vector<T, N1>& lhs, const Vector<T, N2>& rhs) {
    return !(lhs == rhs);
}

template <class T, size_t N>
Vector<T, N> operator+(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
    return lhs.add(rhs);
}

template <class T, size_t N>
Vector<T, N> operator-(const Vector<T, N>& lhs, const Vector<T, N>& rhs) {
    return lhs.add(rhs.opposite());
}

template <class T, size_t N>
Vector<T, N> operator*(const T& scalar, const Vector<T, N>& rhs) {
    return rhs.scalar_multiply(scalar);
}

template <class T, size_t N>
Vector<T, N> operator*(const Vector<T, N>& lhs, const T& scalar) {
    return lhs.scalar_multiply(scalar);
}

template <class T, size_t N>
inline std::ostream& operator<<(std::ostream& os, const Vector<T, N>& rhs) {
    os << "<";
    for (int i = 0; i < N-1; ++i) {
       os << rhs.at(i) << ", "; 
    }
    os << rhs.at(N-1) << ">";
    return os;
}

#endif
