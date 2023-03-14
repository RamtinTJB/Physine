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

    Transform* transform = nullptr;
    Collider* collider = nullptr;

    Object() {
        mass = 0.;
        transform = new Transform();
    }

    void add_collider(Collider* c) { collider = c; }

    ~Object() {
        delete transform;
        if (collider != nullptr)
            delete collider;
    }
};

#endif
