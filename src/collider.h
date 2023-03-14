#ifndef PHYSINE_COLLIDER_H_
#define PHYSINE_COLLIDER_H_

#include "rect.h"
#include "circle.h"

class BoxCollider;
class CircleCollider;

class Collider {
    public:
        virtual bool test_collision(const BoxCollider&) const = 0;
        virtual bool test_collision(const CircleCollider&) const = 0;
        virtual ~Collider() = default;
};

class BoxCollider : public Collider {
    public:
        Rect<double> box;

        bool test_collision(const BoxCollider&) const;
        bool test_collision(const CircleCollider&) const;

        ~BoxCollider() {}
};

class CircleCollider : public Collider {
    public:
        Circle<double> circle;

        bool test_collision(const BoxCollider&) const;
        bool test_collision(const CircleCollider&) const;

        ~CircleCollider() {}
};

#endif
