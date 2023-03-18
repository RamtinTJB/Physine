#ifndef PHYSINE_OBJECT_H_
#define PHYSINE_OBJECT_H_

#include "collider.h"
#include "common.h"
#include "drawable.h"
#include "transform.h"

struct Object {
    double mass;
    bool has_gravity = true;
    bool is_kinetic = true;
    Vector2f velocity;
    

    Transform* transform = nullptr;
    Collider* collider = nullptr;
    Drawable* drawable = nullptr;

    Object() {
        mass = 0.;
        transform = new Transform();
    }

    void add_collider(Collider* c) { collider = c; }

    bool is_drawable() const { return drawable != nullptr; }

    ~Object() {
        delete transform;
        if (collider != nullptr)
            delete collider;
        if (drawable != nullptr)
            delete drawable;
    }
};

#endif
