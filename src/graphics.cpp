#include "graphics.h"

Graphics::Graphics(int width, int height) {
    width_  = width;
    height_ = height;

    window_ = new sf::RenderWindow(sf::VideoMode(width_, height_, 32), "Physine 2D Engine");
}

void Graphics::draw_objects(const std::vector<Object*>& objs) {
    window_->clear(sf::Color::Black);
    for (Object* obj : objs) {
        if (obj->is_drawable()) {
            sf::Sprite sprite(obj->drawable->get_texture().getTexture());
            Vector2f top_left = obj->drawable->get_top_left(obj->transform);
            Vector2f center_offset = obj->transform->position - top_left;
            sprite.setOrigin(center_offset.x(), center_offset.y());
            Vector2f pos = obj->transform->position;
            sprite.setPosition(pos.x(), pos.y());
            sprite.setRotation(obj->transform->rotation);
            window_->draw(sprite);
        }
    }
    window_->display();
}

bool Graphics::has_closed() const {
    sf::Event event;
    while (window_->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_->close();
            return true;
        }
    }
    return false;
}
