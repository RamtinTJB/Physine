#ifndef PHYSINE_DRAWABLE_H_
#define PHYSINE_DRAWABLE_H_

#include <SFML/Graphics.hpp>

#include "transform.h"
#include "color.h"

class Drawable {
    public:
        virtual void render(const Transform*) = 0;

        sf::RenderTexture& get_texture() { return render_texture_; }
        void set_color(const Color& color) { color_ = color; }

        virtual ~Drawable() = default;

    protected:
        sf::RenderTexture render_texture_;
        Color color_;
};

class RectangleShape : public Drawable {
    public:
        void render(const Transform* transform);
};

class CircleShape : public Drawable {
    public:
        void render(const Transform* transform);
};

#endif
