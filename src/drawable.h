#ifndef PHYSINE_DRAWABLE_H_
#define PHYSINE_DRAWABLE_H_

#include <SFML/Graphics.hpp>

#include "transform.h"

class Drawable {
    public:
        virtual void render(const Transform*) = 0;

        sf::RenderTexture& get_texture() { return render_texture_; }

        virtual ~Drawable() = default;

    protected:
        sf::RenderTexture render_texture_;
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
