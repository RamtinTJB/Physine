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

        ObjectBuilder(Object* obj) : obj{obj} {}

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

        ObjectBuilder collider(AbstractCollider* c) {
            obj->collider = c;
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

        ObjectBuilder rotation(float r) {
            obj->transform->rotation = r;
            return *this;
        }

        ObjectBuilder velocity(const Vector2f& v) {
            obj->velocity = v;
            return *this;
        }

        ObjectBuilder angular_velocity(float w) {
            obj->angular_velocity = w;
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

        static ObjectBuilder duplicate(const std::string& new_name, const Object* const obj) {
            Object* dup_obj = new Object(new_name, new Transform(*obj->transform));
            return ObjectBuilder(dup_obj)
                .drawable(obj->drawable->clone())
                .collider(obj->collider->clone(dup_obj->transform))
                .mass(obj->mass)
                .gravity(obj->has_gravity)
                .kinetic(obj->is_kinetic);
        }

        static ObjectBuilder Rectangle(const std::string& name) {
            return ObjectBuilder(name)
                .collider<BoxCollider>()
                .drawable(new RectangleShape());
        }


        static ObjectBuilder Circle(const std::string& name) {
            return ObjectBuilder(name)
                .collider<CircleCollider>()
                .drawable(new CircleShape());
        }

        Object* build() {
            return obj;
        }
};

#endif
