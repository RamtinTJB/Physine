#include "collider.h"
#include <iostream>

bool BoxCollider::test_collision(const BoxCollider* bc) const {
    return box.intersects(bc->box);
}

bool BoxCollider::test_collision(const CircleCollider* cc) const {
    // TODO Implement circle v box collision
    return false;
}

bool CircleCollider::test_collision(const BoxCollider* bc) const {
    return bc->test_collision(this);
}

bool CircleCollider::test_collision(const CircleCollider* cc) const {
    Circle<double> this_circle(transform->position, transform->scale.x()); 
    Circle<double> other_circle(cc->get_transform()->position, cc->get_transform()->scale.x());
    return this_circle.intersects(other_circle);
}
