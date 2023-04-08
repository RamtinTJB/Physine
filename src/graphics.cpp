#include "graphics.h"

Graphics::Graphics(int width, int height) {
    width_  = width;
    height_ = height;

    window_ = new sf::RenderWindow(sf::VideoMode(width_, height_, 32), "Physine 2D Engine");
}

void Graphics::clear_window() {
    window_->clear(BACKGROUND_COLOR);
}

void Graphics::display() {
    window_->display();
}

void Graphics::draw_object(const Object* obj) {
    if (obj->is_drawable()) {
        obj->drawable->draw(window_, obj->transform);
    }
}

void Graphics::close() {
    window_->close();
}
