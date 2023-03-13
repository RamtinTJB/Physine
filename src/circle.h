#ifndef PHYSINE_CIRCLE_H_
#define PHYSINE_CIRCLE_H_

#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <vector>

#include "common.h"
#include "constants.h"

template <class T>
struct Circle {
    static_assert(std::is_arithmetic<T>::value, "Circle requires an arithmetic data type");

    T x;
    T y;
    T radius;

    constexpr Circle(const T& x, const T& y, const T& radius) :
        x{x}, y{y}, radius{radius} {}

    constexpr Circle(const Vector2<T>& position, const T& radius) :
        x{position[0]}, y{position[1]}, radius{radius} {}

    constexpr Circle(const Circle<T>& other) {
        x = other.x;
        y = other.y;
        radius = other.radius;
    }

    constexpr explicit Circle(std::initializer_list<T> list) {
        std::vector v(list);
        if (list.size() != 3)
            throw std::invalid_argument("Too many or too few arguments provided to construct Circle");
        x = v[0]; y = v[1]; radius = v[2];
    }

    constexpr void operator=(const Circle<T>& other) {
        x = other.x;
        y = other.y;
        radius = other.radius;
    }

    constexpr T area() const { return PI*radius*radius; }
    constexpr T circumference() const { return 2*PI*radius; }

    constexpr bool contains(const Vector2<T>& point) const {
        return contains(point[0], point[1]);
    }

    constexpr bool contains(const T& x_, const T& y_) const {
        return ((x-x_)*(x-x_) + (y-y_)*(y-y_)) < radius*radius;
    }

    constexpr bool intersects(const Circle<T>& other) const {
        return std::sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y)) < radius + other.radius;
    }

    constexpr Circle<T>& operator+=(const Vector2<T>& other) {
        x += other[0];
        y += other[1];
        return *this;
    }

    constexpr Circle<T>& operator-=(const Vector2<T>& other) {
        x -= other[0];
        y -= other[1];
        return *this;
    }
};

template <class T>
inline bool operator==(const Circle<T>& lhs, const Circle<T>& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.radius == rhs.radius);
}

template <class T>
inline bool operator!=(const Circle<T>& lhs, const Circle<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
inline Circle<T> operator+(Circle<T> lhs, const Vector2<T>& rhs) {
    lhs += rhs;
    return lhs;
}

template <class T>
inline Circle<T> operator-(Circle<T> lhs, const Vector2<T>& rhs) {
    lhs -= rhs;
    return lhs;
}

#endif
