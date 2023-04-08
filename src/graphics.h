#ifndef PHYSINE_GRAPHICS_H_
#define PHYSINE_GRAPHICS_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "object.h"


class Graphics {
    public:
        Graphics(int width, int height);

        void draw_object(const Object*);
        void clear_window();
        void display();
        void close();
        sf::RenderWindow* get_window() { return window_; }

    private:
        sf::RenderWindow* window_ = nullptr;
        int width_, height_;

        sf::Color BACKGROUND_COLOR = sf::Color::Black;
};

#endif
