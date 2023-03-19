#ifndef PHYSINE_COLLIDER_H_
#define PHYSINE_COLLIDER_H_

#include <cmath>
#include <iostream>

#include "rect.h"
#include "circle.h"
#include "transform.h"

enum class ColliderType { CIRCLE, BOX };

class BoxCollider;
class CircleCollider;

class Collider {
    public:
        Collider(Transform* t) : transform{t} {}
        virtual bool test_collision(const Collider*) const = 0;
        virtual bool test_collision(const BoxCollider*) const = 0;
        virtual bool test_collision(const CircleCollider*) const = 0;
        virtual ~Collider() = default;

        Transform* get_transform() const { return transform; }
        ColliderType type() const { return type_; }

    protected:
        Transform* transform;
        ColliderType type_;
};

class BoxCollider : public Collider {
    public:
        BoxCollider(Transform* t) : Collider(t) {
            type_ = ColliderType::BOX;
        }

        bool test_collision(const Collider*) const { return false; }
        bool test_collision(const BoxCollider*) const;
        bool test_collision(const CircleCollider*) const;

        ~BoxCollider() {}
};

class CircleCollider : public Collider {
    public:
        CircleCollider(Transform* t) : Collider(t) {
            type_ = ColliderType::CIRCLE;
        }

        bool test_collision(const Collider*) const { return false; }
        bool test_collision(const BoxCollider*) const;
        bool test_collision(const CircleCollider*) const;

        ~CircleCollider() {}
};

#endif
