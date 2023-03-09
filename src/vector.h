#ifndef PHYSINE_VECTOR_H_
#define PHYSINE_VECTOR_H_

#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <type_traits>

#include "constants.h"

template <class T, size_t N>
class Vector {
    private:
        T* vector_ = new T[N];

    public:
        typedef T value_type;
        constexpr size_t dimension() const noexcept { return N; }

        T& at(size_t index) const {
            if (index >= N || index < 0) throw std::out_of_range("Index out of bounds");
            return vector_[index];
        }

        T& operator[](size_t index) const {
            return at(index);
        } 

        double magnitude() const noexcept {
            if (N == 0) return 0;
            double sum_squares = 0;
            for (int i = 0; i < N; ++i) {
                sum_squares += vector_[i] * vector_[i];
            }
            return std::sqrt(sum_squares);
        }

        double size() const noexcept { return magnitude(); }

        double dot(const Vector<T, N>& other) const {
            if (N == 0) return 0;
            double result = 0;
            for (int i = 0; i < N; ++i) {
                result += vector_[i] * other.vector_[i];
            }
            return result;
        }

        Vector<T, 3> cross(const Vector<T, 3>& other) const {
            if (N != 3) {
                throw std::logic_error("Cross product only applies to 3 dimensional vectors.");
            }
            Vector<T, 3> res;
            res[0] = vector_[1]*other[2] - other[1]*vector_[2];
            res[1] = vector_[2]*other[0] - other[2]*vector_[0];
            res[2] = vector_[0]*other[1] - other[0]*vector_[1];
            return res;
        }

        Vector<T, N> add(const Vector<T, N>&other) const {
            Vector<T, N> new_vector;
            for (int i = 0; i < N; ++i) {
                new_vector.vector_[i] = vector_[i] + other.vector_[i];
            }
            return new_vector;
        }

        Vector<T, N> scalar_multiply(const T& scalar) const {
            Vector<T, N> new_vector;
            for (int i = 0; i < N; ++i) {
                new_vector.vector_[i] = vector_[i] * scalar;
            }
            return new_vector;
        }

        Vector<T, N> opposite() const {
            return scalar_multiply(-1);
        }

        Vector<T, N> unit() const {
            return scalar_multiply(1.0/magnitude());
        }

        Vector<T, N> projection_unto(const Vector<T, N>& other) const {
            return other.scalar_multiply((dot(other))/(other.dot(other)));
        }

        Vector() {
            for (int i = 0; i < N; ++i) {
                vector_[i] = 0;
            }
        }

        explicit Vector(std::initializer_list<T> list) {
            if (list.size() != N) {
                throw std::invalid_argument("Number of elements in the initializer list doesn't match the dimension of the vector.");
            }
            std::copy(list.begin(), list.end(), vector_);
        }

        Vector(const Vector<T, N>& other) {
            std::copy(other.vector_, other.vector_ + N, vector_);
        }

        void operator=(const Vector<T, N>& other) {
            std::copy(other.vector_, other.vector_ + N, vector_);
        }

        Vector<T, N>& operator+=(const Vector<T, N>& rhs) {
            for (int i = 0; i < N; ++i) {
                vector_[i] += rhs.vector_[i];
            }
            return *this;
        }

        Vector<T, N>& operator-=(const Vector<T, N>& rhs) {
            for (int i = 0; i < N; ++i) {
                vector_[i] -= rhs.vector_[i];
            }
            return *this;
        }

        Vector<T, N> operator-() {
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
inline std::ostream& operator<<(std::ostream& os, const Vector<T, N>& rhs) {
    os << "<";
    for (int i = 0; i < N-1; ++i) {
       os << rhs.at(i) << ", "; 
    }
    os << rhs.at(N-1) << ">";
    return os;
}

#endif
