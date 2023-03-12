#ifndef PHYSINE_RECT_H_
#define PHYSINE_RECT_H_

#include <type_traits>

#include "common.h"

template <class T>
struct Rect {
    static_assert(std::is_arithmetic<T>::value, "Rect requires an arithmetic data type");

    T x;
    T y;
    T width;
    T height;

    constexpr Rect(const T& x, const T& y, const T& width, const T& height) :
        x{x}, y{y}, width{width}, height{height} {}

    constexpr Rect(const Vector2<T>& position, const Vector2<T>& size) :
        x{position[0]}, y{position[1]}, width{size[0]}, height{size[1]} {}

    constexpr Rect(const Rect<T>& other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }

    constexpr void operator=(const Rect<T>& other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }

    constexpr T area() const { return width * height; }
    constexpr T perimeter() const { return 2*(width+height); }

    constexpr bool contains(const Vector2<T>& point) const {
        return contains(point[0], point[1]);
    }

    constexpr bool contains(const T& x_, const T& y_) const {
        return (x_ >= x && x_ <= x+width
                && y_ >= y && y_ <= y+height);
    }

    // TODO Implement all member functions
    constexpr bool intersects(const Rect<T>& other) const;
};

template <class T>
inline bool operator==(const Rect<T>& lhs, const Rect<T>& rhs) {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y) &&
        (lhs.width == rhs.width) && (lhs.height == rhs.height);
}

template <class T>
inline bool operator!=(const Rect<T>& lhs, const Rect<T>& rhs) {
    return !(lhs == rhs);
}

#endif
