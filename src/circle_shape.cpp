#include "drawable.h"

void CircleShape::render(const Transform* transform) {
    render_texture_.create(2*transform->scale.x(), 2*transform->scale.y());
    render_texture_.clear(sf::Color::Black);
    sf::CircleShape c;
    c.setRadius(transform->scale[0]);
    c.setFillColor(sf::Color(255, 255, 255));
    render_texture_.draw(c);
    render_texture_.display();
}
