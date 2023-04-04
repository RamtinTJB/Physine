#ifndef PHYSINE_MATH_H_
#define PHYSINE_MATH_H_

#include <type_traits>
#include <cmath>

#include "common.h"

double degree_to_radian(double degree);
double radian_to_degree(double radian);
Vector2f rotate_rad(const Vector2f& input, const Vector2f& origin, double angle_rad);
Vector2f rotate(const Vector2f& input, const Vector2f& origin, double angle_deg);

template <class T>
class Approx {
    static_assert(std::is_arithmetic<T>::value, "Can't approximate non-floating point types.");
    public:
        Approx() = delete;
        Approx(const Approx& other) = delete;
        Approx operator=(const Approx& other) = delete;

        Approx(T number) { number_ = number; }
        Approx<T>& epsilon(T e) { 
            epsilon_ = e;
            return *this;
        }
        Approx<T>& epsilon_ratio(T e) {
            epsilon_ = e*number_;
            return *this;
        }

        constexpr T number() const { return number_; }
        constexpr T epsilon() const { return epsilon_; }

    private:
        T number_;
        T epsilon_ = 0.0001;
};

template <class T>
inline bool operator==(T lhs, const Approx<T>& rhs) {
    return std::abs(lhs - rhs.number()) < rhs.epsilon();
}

template <class T>
inline bool operator!=(T lhs, const Approx<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
inline bool operator==(const Approx<T>& lhs, T rhs) {
    return rhs == lhs;
}

template <class T>
inline bool operator!=(const Approx<T>& lhs, T rhs) {
    return !(lhs == rhs);
}

#endif
