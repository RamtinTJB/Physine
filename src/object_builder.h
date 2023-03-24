#ifndef PHYSINE_OBJECT_BUILDER_H_
#define PHYSINE_OBJECT_BUILDER_H_

#include "object.h"

class ObjectBuilder {
    private:
        Object* obj;

    public:
        ObjectBuilder(const std::string& name) {
            obj = new Object(name);
        }

        ObjectBuilder drawable(Drawable* drawable_) {
            obj->drawable = drawable_;
            return *this;
        }

        ObjectBuilder color(const Color& c) {
            obj->drawable->set_color(c);
            return *this;
        }

        template <class T>
        ObjectBuilder collider() {
            obj->collider = new T(obj->transform);
            return *this;
        }

        ObjectBuilder position(const Vector2f& p) {
            obj->transform->position = p;
            return *this;
        }

        ObjectBuilder scale(const Vector2f& s) {
            obj->transform->scale = s;
            return *this;
        }

        ObjectBuilder velocity(const Vector2f& v) {
            obj->velocity = v;
            return *this;
        }

        ObjectBuilder mass(double m) {
            obj->mass = m;
            return *this;
        }

        ObjectBuilder gravity(bool g) {
            obj->has_gravity = g;
            return *this;
        }

        ObjectBuilder kinetic(bool k) {
            obj->is_kinetic = k;
            return *this;
        }

        Object* build() {
            return obj;
        }
};

#endif
