#ifndef PHYSINE_OBJECT_H_
#define PHYSINE_OBJECT_H_

#include "collider.h"
#include "common.h"
#include "drawable.h"
#include "transform.h"

/* class Collider; */

/* struct Transform { */
/*     Vector2f position; */
/*     Vector2f scale; */
/*     Vector2f rotation; */
/* }; */

struct Object {
    double mass;
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
    }
};

#endif
