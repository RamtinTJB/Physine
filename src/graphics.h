#ifndef PHYSINE_GRAPHICS_H_
#define PHYSINE_GRAPHICS_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "object.h"

class Graphics {
    public:
        Graphics(int width, int height);
        void draw_objects(const std::vector<Object*>& objs);
        bool has_closed() const;

    private:
        sf::RenderWindow* window_ = nullptr;
        int width_, height_;
};

#endif
