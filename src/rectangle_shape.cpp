#include "drawable.h"

void RectangleShape::render(const Transform* transform) {
    render_texture_.create(transform->scale.x(), transform->scale.y());
    render_texture_.clear(Color::TRANSPARENT);
    sf::RectangleShape r;
    r.setSize(sf::Vector2f(transform->scale.x(), transform->scale.y()));
    r.setFillColor(color_);
    render_texture_.draw(r);
    render_texture_.display();
}

Vector2f RectangleShape::get_top_left(const Transform* t) const {
    double width = t->scale.x();
    double height = t->scale.y();
    return Vector2f{t->position.x() - width/2, t->position.y() - height/2};
}
