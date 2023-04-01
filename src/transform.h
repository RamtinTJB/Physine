#ifndef PHYSINE_TRANSFORM_H_
#define PHYSINE_TRANSFORM_H_

#include <iostream>

#include "common.h"

struct Transform {
    Vector2f position;
    Vector2f scale {1, 1};
    float rotation;

    Transform() = default;
    Transform(const Transform& other) {
        position = other.position;
        scale = other.scale;
        rotation = other.rotation;
    }

    Transform& operator=(const Transform& other) {
        position = other.position;
        scale = other.scale;
        rotation = other.rotation;
        return *this;
    }

    ~Transform() = default;
};

inline std::ostream& operator<<(std::ostream& os, const Transform& transform) {
    os << "Position: " << transform.position << std::endl;
    os << "Scale:    " << transform.scale << std::endl;
    os << "Rotation: " << transform.rotation << std::endl;
    return os;
}

#endif
