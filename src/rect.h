#ifndef PHYSINE_RECT_H_
#define PHYSINE_RECT_H_

#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <vector>

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

    constexpr Rect(const Vector2f& position, const Vector2f& size) :
        x{position[0]}, y{position[1]}, width{size[0]}, height{size[1]} {}

    constexpr static Rect fromCenter(const Vector2f& center, const Vector2f& size) {
        double x = center.x() - size.x()/2;
        double y = center.y() - size.y()/2;
        return Rect(Vector2f{x, y}, size);
    }

    constexpr Rect(const Rect<T>& other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }

    constexpr explicit Rect(std::initializer_list<T> list) {
        std::vector v(list);
        if (list.size() != 4)
            throw std::invalid_argument("Too many or too few arguments provided to construct Rect");
        x = v[0]; y = v[1]; width = v[2]; height = v[3];
    }

    constexpr void operator=(const Rect<T>& other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }

    constexpr T area() const { return width * height; }
    constexpr T perimeter() const { return 2*(width+height); }

    Vector2f center() const {
        return Vector2f {(x+width)/2, (y+height)/2};
    }

    Vector2f top_left() const {
        return Vector2f{x, y};
    }
    
    Vector2f top_right() const {
        return Vector2f{x+width, y};
    }

    Vector2f bottom_left() const {
        return Vector2f{x, y+height};
    }

    Vector2f bottom_right() const {
        return Vector2f{x+width, y+height};
    }

    std::vector<Vector2f> get_corners() const {
        return std::vector<Vector2f> {top_left(), top_right(),
                                      bottom_left(), bottom_right()};
    }

    constexpr bool contains(const Vector2f& point) const {
        return contains(point[0], point[1]);
    }

    constexpr bool contains(const T& x_, const T& y_) const {
        return (x_ >= x && x_ <= x+width
                && y_ >= y && y_ <= y+height);
    }

    constexpr bool intersects(const Rect<T>& other) const {
        return ((x < other.x+other.width) && (other.x < x+width)
                && (y < other.y+other.height) && (other.y < y+height)); 
    }

    constexpr Rect<T> intersection(const Rect<T>& other) const {
        if (intersects(other)) {
            T x1 = std::max(x, other.x);
            T y1 = std::max(y, other.y);
            T x2 = std::min(x+width, other.x+other.width);
            T y2 = std::min(y+height, other.y+other.height);
            return Rect<T>{x1, y1, x2-x1, y2-y1};
        } else {
            return Rect<T>{0, 0, 0, 0};
        }
    }

    constexpr Rect<T>& operator+=(const Vector2f& other) {
        x += other[0];
        y += other[1];
        return *this;
    }

    constexpr Rect<T>& operator-=(const Vector2f& other) {
        x -= other[0];
        y -= other[1];
        return *this;
    }
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

template <class T>
inline Rect<T> operator+(Rect<T> lhs, const Vector2f& rhs) {
    lhs += rhs;
    return lhs;
}

template <class T>
inline Rect<T> operator-(Rect<T> lhs, const Vector2f& rhs) {
    lhs -= rhs;
    return lhs;
}

#endif
