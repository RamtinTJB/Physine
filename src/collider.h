#ifndef PHYSINE_COLLIDER_H_
#define PHYSINE_COLLIDER_H_

#include <cmath>
#include <iostream>

#include "rect.h"
#include "circle.h"
#include "transform.h"

enum class ColliderType { GENERIC, CIRCLE, BOX };

class BoxCollider;
class CircleCollider;

class Collider {
    public:
        typedef Collider* type;
        Collider(Transform* t) : transform{t} {}
        virtual bool test_collision(const Collider*) const = 0;
        virtual bool test_collision(const BoxCollider*) const = 0;
        virtual bool test_collision(const CircleCollider*) const = 0;
        virtual ~Collider() = default;

        Transform* get_transform() const { return transform; }
        ColliderType get_type() const { return type_; }

    protected:
        Transform* transform;
        ColliderType type_;
};

class BoxCollider : public Collider {
    public:
        typedef BoxCollider* type;
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
        typedef CircleCollider* type;
        CircleCollider(Transform* t) : Collider(t) {
            type_ = ColliderType::CIRCLE;
        }

        bool test_collision(const Collider*) const { return false; }
        bool test_collision(const BoxCollider*) const;
        bool test_collision(const CircleCollider*) const;

        ~CircleCollider() {}
};

template <ColliderType T> struct CollType {
    using type = Collider::type;
};

template <> struct CollType<ColliderType::BOX> {
    using type = BoxCollider::type;
};

template <> struct CollType<ColliderType::CIRCLE> {
    using type = CircleCollider::type;
};

#endif
