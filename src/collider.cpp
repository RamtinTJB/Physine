#include "collider.h"

#include "debug.h"
#include "ph_math.h"

CollisionPoints BoxCollider::test_collision([[maybe_unused]] const BoxCollider* bc) const {
    // TODO Fix this
    //return box.intersects(bc->box);
    return CollisionPoints();
}

CollisionPoints BoxCollider::test_collision(const CircleCollider* cc) const {
    Transform* circle_t = cc->get_transform();
    Vector2f rect_center = transform->position;
    Vector2f rect_size = transform->scale;
    Vector2f circle_center_rotated = rotate(circle_t->position, rect_center, -transform->rotation);
    Rect<double> rect = Rect<double>::fromCenter(rect_center, rect_size);
    Circle<double> other_circle(circle_center_rotated, circle_t->scale.x());

    CollisionPoints col;
    
    if (std::abs(other_circle.x - rect_center.x()) < rect.width/2) {
        if (std::abs(other_circle.y - rect_center.y()) <
                other_circle.radius + rect.height/2) {
            col.has_collision = true;
            col.normal = Vector2f{0, other_circle.y - rect_center.y()};
            double total_length = rect.height/2 + other_circle.radius;
            double center_distance = other_circle.center().distance(
                    Vector2f{other_circle.x, rect_center.y()}
                    );
            col.overlap_length = total_length - center_distance;
        }
    }
    else if (std::abs(circle_t->position.y() - rect_center.y()) < rect.height/2) {
        if (std::abs(circle_t->position.x() - rect_center.x()) <
                circle_t->scale.x() + rect.width/2) {
            col.has_collision = true;
            col.normal = Vector2f{circle_t->position.x() - rect_center.x(), 0};
            double total_length = rect.width/2 + other_circle.radius;
            double center_distance = other_circle.center().distance(
                    Vector2f{rect_center.x(), other_circle.y}
                    );
            col.overlap_length = total_length - center_distance;
        }
    } else {
        std::vector<Vector2f> corners = rect.get_corners();
        for (const Vector2f& corner : corners) {
            double total_distance = other_circle.center().distance(corner);
            if (total_distance < other_circle.radius) {
                col.has_collision = true;
                col.normal = other_circle.center() - corner;
//                col.overlap_length = total_distance - other_circle.radius;
                col.overlap_length = 0;
                break;
            }
        }
    }
    if (col.has_collision)
        col.normal = rotate(col.normal, Vector2f(), transform->rotation);
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
