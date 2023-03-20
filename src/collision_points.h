#ifndef PHYSINE_COLLISION_POINTS_H_
#define PHYSINE_COLLISION_POINTS_H_

#include "common.h"

struct CollisionPoints {
    Vector2f normal;
    bool has_collision = false;

    CollisionPoints() = default;
};

#endif
