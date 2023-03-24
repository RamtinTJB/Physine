#ifndef PHYSINE_COLLISION_POINTS_H_
#define PHYSINE_COLLISION_POINTS_H_

#include "common.h"

struct CollisionPoints {
    Vector2f normal;
    double overlap_length;
    bool has_collision = false;

    CollisionPoints() = default;
};

#endif
