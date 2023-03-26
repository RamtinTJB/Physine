#ifndef PHYSINE_COLLIDER_H_
#define PHYSINE_COLLIDER_H_

#include <cmath>
#include <iostream>

#include "rect.h"
#include "circle.h"
#include "transform.h"
#include "vector.h"
#include "collision_points.h"

enum class ColliderType { GENERIC, CIRCLE, BOX };

class BoxCollider;
class CircleCollider;

class AbstractCollider {
    public:
        AbstractCollider(Transform* t) : transform{t} {}
        virtual CollisionPoints test_collision(const AbstractCollider*) const = 0;
        virtual CollisionPoints test_collision(const BoxCollider*) const = 0;
        virtual CollisionPoints test_collision(const CircleCollider*) const = 0;
        virtual ~AbstractCollider() = default;

        virtual AbstractCollider* clone(Transform* transform) const = 0;

        Transform* get_transform() const { return transform; }
        ColliderType get_type() const { return type_; }

    protected:
        Transform* transform;
        ColliderType type_;
};

template <class Derived>
class Collider : public AbstractCollider {
    public:
        Collider(Transform* t) : AbstractCollider(t) {}
        virtual AbstractCollider* clone(Transform* transform) const override {
            return new Derived(transform); 
        }
};

class BoxCollider : public Collider<BoxCollider> {
    public:
        typedef BoxCollider* type;
        BoxCollider(Transform* t) : Collider(t) {
            type_ = ColliderType::BOX;
        }

        CollisionPoints test_collision(const AbstractCollider*) const { return CollisionPoints(); }
        CollisionPoints test_collision(const BoxCollider*) const;
        CollisionPoints test_collision(const CircleCollider*) const;

        ~BoxCollider() {}
};

class CircleCollider : public Collider<CircleCollider> {
    public:
        typedef CircleCollider* type;
        CircleCollider(Transform* t) : Collider(t) {
            type_ = ColliderType::CIRCLE;
        }

        CollisionPoints test_collision(const AbstractCollider*) const { return CollisionPoints(); }
        CollisionPoints test_collision(const BoxCollider*) const;
        CollisionPoints test_collision(const CircleCollider*) const;

        ~CircleCollider() {}
};

#endif
