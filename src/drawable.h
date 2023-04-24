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
        virtual void draw(sf::RenderWindow*, const Transform*) const = 0;

        sf::RenderTexture& get_texture() { return render_texture_; }
        void set_color(const Color& color) { color_ = color; }
        Color get_color() const { return color_; }

        virtual ~Drawable() = default;

        virtual Drawable* clone() const = 0;

        Drawable() = default;
        Drawable(const Drawable& other) {
            color_ = other.color_;
        }

    protected:
        sf::RenderTexture render_texture_;
        Color color_;
};

template <class Derived>
class DrawableDerivationHelper : public Drawable {
    virtual Drawable* clone() const override {
        return new Derived(static_cast<Derived const&>(*this));
    }
};

class RectangleShape : public DrawableDerivationHelper<RectangleShape> {
    public:
        void render(const Transform*) override;
        Vector2f get_top_left(const Transform*) const override;
        void draw(sf::RenderWindow*, const Transform*) const override;

        RectangleShape() = default;
        RectangleShape(const RectangleShape& other) {
            color_ = other.color_;
        }
};

class CircleShape : public DrawableDerivationHelper<CircleShape> {
    public:
        void render(const Transform*) override;
        Vector2f get_top_left(const Transform*) const override;
        void draw(sf::RenderWindow*, const Transform*) const override;

        CircleShape() = default;
        CircleShape(const CircleShape& other) {
            color_ = other.color_;
        }
};

class ImageDrawable : public DrawableDerivationHelper<ImageDrawable> {
    public:
        void render(const Transform*) override;
        Vector2f get_top_left(const Transform*) const override;
        void draw(sf::RenderWindow*, const Transform*) const override;

        ImageDrawable() = delete;
        ImageDrawable(const std::string& image_path) {
            image_path_ = image_path;
            load_image();
        }
        ImageDrawable(const ImageDrawable& other) {
            image_path_ = other.image_path_;
            load_image();
        }

    private:
        void load_image();
        std::string image_path_;
        sf::Texture texture_;
};

class TextDrawable : public DrawableDerivationHelper<TextDrawable> {
    public:
        void render(const Transform*) override;
        Vector2f get_top_left(const Transform*) const override;
        void draw(sf::RenderWindow*, const Transform*) const override;

        TextDrawable() = default;
        TextDrawable(const TextDrawable& other) {
            text_ = other.text_;
        }

        void text(const std::string& text) { text_ = text; }
        std::string text() const { return text_; }

    private:
        std::string text_ = "";
};

#endif
