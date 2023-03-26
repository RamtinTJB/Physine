#ifndef PHYSINE_DRAWABLE_H_
#define PHYSINE_DRAWABLE_H_

#include <SFML/Graphics.hpp>

#include "transform.h"
#include "color.h"
#include "vector.h"

class Drawable {
    public:
        virtual void render(const Transform*) = 0;
        virtual Vector2f get_top_left(const Transform*) const = 0;

        sf::RenderTexture& get_texture() { return render_texture_; }
        void set_color(const Color& color) { color_ = color; }
        Color get_color() const { return color_; }

        virtual ~Drawable() = default;

    protected:
        sf::RenderTexture render_texture_;
        Color color_;
};

class RectangleShape : public Drawable {
    public:
        void render(const Transform* transform) override;
        Vector2f get_top_left(const Transform* t) const override;
};

class CircleShape : public Drawable {
    public:
        void render(const Transform* transform) override;
        Vector2f get_top_left(const Transform* t) const override;
};

#endif
