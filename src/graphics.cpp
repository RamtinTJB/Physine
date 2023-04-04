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
            obj->drawable->draw(window_, obj->transform);
        }
    }
    window_->display();
}

void Graphics::close() {
    window_->close();
}
