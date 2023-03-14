#ifndef PHYSINE_OBJECT_H_
#define PHYSINE_OBJECT_H_

#include "collider.h"
#include "common.h"

class Collider;

struct Transform {
    Vector2f position;
    Vector2f scale;
    Vector2f rotation;
};

struct Object {
    double mass;
    Vector2f velocity;

    Transform* transform;
    Collider* collider;
};

#endif
