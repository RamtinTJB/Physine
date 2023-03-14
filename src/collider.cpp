#include "collider.h"

bool BoxCollider::test_collision(const BoxCollider& bc) const {
    return box.intersects(bc.box);
}

bool BoxCollider::test_collision(const CircleCollider& cc) const {
    // TODO Implement circle v box collision
    return false;
}

bool CircleCollider::test_collision(const BoxCollider& bc) const {
    return bc.test_collision(*this);
}

bool CircleCollider::test_collision(const CircleCollider& cc) const {
    return circle.intersects(cc.circle);
}
