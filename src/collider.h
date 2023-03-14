#ifndef PHYSINE_OBJECT_H_
#define PHYSINE_OBJECT_H_

#include "rect.h"
#include "circle.h"

class BoxCollider;
class CircleCollider;

class Collider {
    public:
        virtual bool test_collision(const BoxCollider&) const = 0;
        virtual bool test_collision(const CircleCollider&) const = 0;
};

class BoxCollider : public Collider {
    public:
        Rect<double> box;

        bool test_collision(const BoxCollider&) const;
        bool test_collision(const CircleCollider&) const;
};

class CircleCollider : public Collider {
    public:
        Circle<double> circle;

        bool test_collision(const BoxCollider&) const;
        bool test_collision(const CircleCollider&) const;
};

#endif
