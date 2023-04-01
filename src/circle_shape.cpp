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

void CircleShape::draw(sf::RenderWindow* window, const Transform* transform) const {
    sf::Sprite sprite(render_texture_.getTexture());
    Vector2f top_left = get_top_left(transform);
    Vector2f center = transform->position;
    Vector2f center_offset = center - top_left;
    sprite.setOrigin(center_offset.x(), center_offset.y());
    sprite.setPosition(center.x(), center.y());
    sprite.setRotation(transform->rotation);
    window->draw(sprite);
}
