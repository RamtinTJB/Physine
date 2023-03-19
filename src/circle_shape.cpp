#include "drawable.h"

void CircleShape::render(const Transform* transform) {
    render_texture_.create(2*transform->scale.x(), 2*transform->scale.y());
    render_texture_.clear(TRANSPARENT);
    sf::CircleShape c;
    c.setRadius(transform->scale[0]);
    c.setFillColor(color_);
    render_texture_.draw(c);
    render_texture_.display();
}
