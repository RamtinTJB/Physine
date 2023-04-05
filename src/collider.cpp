#include "collider.h"

#include "debug.h"
#include "ph_math.h"

CollisionPoints BoxCollider::test_collision(const BoxCollider* bc) const {
    // TODO Fix this
    //return box.intersects(bc->box);
    return CollisionPoints();
}

CollisionPoints BoxCollider::test_collision(const CircleCollider* cc) const {
    Transform* circle_t = cc->get_transform();
    //Circle<double> other_circle(circle_t->position, circle_t->scale.x());
    Vector2f rect_center = transform->position;
    Vector2f rect_size = transform->scale;
    Vector2f circle_center_rotated = rotate(circle_t->position, rect_center, -transform->rotation);
    Circle<double> other_circle(circle_center_rotated, circle_t->scale.x());

    CollisionPoints col;
    
    if (std::abs(other_circle.x - rect_center.x()) < rect_size.x()/2) {
        if (std::abs(other_circle.y - rect_center.y()) <
                other_circle.radius + rect_size.y()/2) {
            col.has_collision = true;
            col.normal = Vector2f{0, other_circle.y - rect_center.y()};
            double total_length = rect_size.y()/2 + other_circle.radius;
            double center_distance = other_circle.center().distance(
                    Vector2f{other_circle.x, rect_center.y()}
                    );
            col.overlap_length = total_length - center_distance;
        }
    }
    if (std::abs(circle_t->position.y() - rect_center.y()) < rect_size.y()/2) {
        if (std::abs(circle_t->position.x() - rect_center.x()) <
                circle_t->scale.x() + rect_size.x()/2) {
            col.has_collision = true;
            col.normal = Vector2f{circle_t->position.x() - rect_center.x(), 0};
            double total_length = rect_size.x()/2 + other_circle.radius;
            double center_distance = other_circle.center().distance(
                    Vector2f{rect_center.x(), other_circle.y}
                    );
            col.overlap_length = total_length - center_distance;
        }
    }
    if (col.has_collision)
        std::cout << col.normal << std::endl;
    col.normal = rotate(col.normal, Vector2f(), transform->rotation);
    if (col.has_collision)
        std::cout << col.normal << std::endl;
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
        double center_distance = this_circle.center().distance(other_circle.center());
        double total_radius = this_circle.radius + other_circle.radius;
        col.overlap_length = total_radius - center_distance;
    }
    return col;
}
