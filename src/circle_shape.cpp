#include "drawable.h"

void CircleShape::render(const Transform* transform) {
    render_texture_.create(2*transform->scale.x(), 2*transform->scale.x());
    render_texture_.clear(Color::TRANSPARENT);
    sf::CircleShape c;
    c.setRadius(transform->scale[0]);
    c.setFillColor(color_);
    render_texture_.draw(c);
    render_texture_.display();
}

Vector2f CircleShape::get_top_left(const Transform* t) const {
    double radius = t->scale.x();
    return Vector2f{t->position.x() - radius, t->position.y() - radius}; 
}
