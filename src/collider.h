#ifndef PHYSINE_COLLIDER_H_
#define PHYSINE_COLLIDER_H_

#include "rect.h"
#include "circle.h"
#include "transform.h"

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

        Transform* transform;
};

class BoxCollider : public Collider {
    public:
        Rect<double> box;

        bool test_collision(const Collider*) const { return false; }
        bool test_collision(const BoxCollider*) const;
        bool test_collision(const CircleCollider*) const;

        ~BoxCollider() {}
};

class CircleCollider : public Collider {
    public:
        using Collider::Collider;

        bool test_collision(const Collider*) const { return false; }
        bool test_collision(const BoxCollider*) const;
        bool test_collision(const CircleCollider*) const;

        ~CircleCollider() {}
};

#endif
