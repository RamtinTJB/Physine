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
            Vector2f pos = obj->drawable->get_top_left(obj->transform);
            sprite.setPosition(pos.x(), pos.y());
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
