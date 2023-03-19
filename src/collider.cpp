#include "collider.h"

#include "debug.h"

bool BoxCollider::test_collision(const BoxCollider* bc) const {
    // TODO Fix this
    //return box.intersects(bc->box);
    return false;
}

bool BoxCollider::test_collision(const CircleCollider* cc) const {
    Transform* circle_t = cc->get_transform();
    Vector2f rect_center = transform->position;
    Vector2f rect_size = transform->scale;
    
    if (std::abs(circle_t->position.x() - rect_center.x()) < rect_size.x()/2) {
        if (std::abs(circle_t->position.y() - rect_center.y()) <
                circle_t->scale.x() + rect_size.y()/2) {
            return true;
        }
    }
    if (std::abs(circle_t->position.y() - rect_center.y()) < rect_size.y()/2) {
        if (std::abs(circle_t->position.x() - rect_center.x()) <
                circle_t->scale.x() + rect_size.x()/2) {
            return true;
        }
    }
    // TODO Implement corner collisions
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
