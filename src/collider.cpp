#include "collider.h"

#include "debug.h"

CollisionPoints BoxCollider::test_collision(const BoxCollider* bc) const {
    // TODO Fix this
    //return box.intersects(bc->box);
    return CollisionPoints();
}

CollisionPoints BoxCollider::test_collision(const CircleCollider* cc) const {
    Transform* circle_t = cc->get_transform();
    Vector2f rect_center = transform->position;
    Vector2f rect_size = transform->scale;

    CollisionPoints col;
    
    if (std::abs(circle_t->position.x() - rect_center.x()) < rect_size.x()/2) {
        if (std::abs(circle_t->position.y() - rect_center.y()) <
                circle_t->scale.x() + rect_size.y()/2) {
            col.has_collision = true;
            col.normal = Vector2f{0, circle_t->position.y() - rect_center.y()};
        }
    }
    if (std::abs(circle_t->position.y() - rect_center.y()) < rect_size.y()/2) {
        if (std::abs(circle_t->position.x() - rect_center.x()) <
                circle_t->scale.x() + rect_size.x()/2) {
            col.has_collision = true;
            col.normal = Vector2f{circle_t->position.x() - rect_center.x(), 0};
        }
    }
    // TODO Implement corner collisions
    return col;
}

CollisionPoints CircleCollider::test_collision(const BoxCollider* bc) const {
    return bc->test_collision(this);
}

CollisionPoints CircleCollider::test_collision(const CircleCollider* cc) const {
    CollisionPoints col;
    Circle<double> this_circle(transform->position, transform->scale.x()); 
    Circle<double> other_circle(cc->get_transform()->position, cc->get_transform()->scale.x());
    if (this_circle.intersects(other_circle)) {
        col.has_collision = true;
        col.normal = Vector2f{other_circle.x - this_circle.x, other_circle.y - this_circle.y};
    }
    return col;
}
