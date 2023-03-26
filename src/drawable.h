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

        virtual Drawable* clone() const = 0;

    protected:
        sf::RenderTexture render_texture_;
        Color color_;
};

template <class Derived>
class DrawableDerivationHelper : public Drawable {
    virtual Drawable* clone() const override {
        Derived* derived = new Derived();
        derived->set_color(this->get_color());
        return derived;
    }
};

class RectangleShape : public DrawableDerivationHelper<RectangleShape> {
    public:
        void render(const Transform* transform) override;
        Vector2f get_top_left(const Transform* t) const override;
};

class CircleShape : public DrawableDerivationHelper<CircleShape> {
    public:
        void render(const Transform* transform) override;
        Vector2f get_top_left(const Transform* t) const override;
};

#endif
