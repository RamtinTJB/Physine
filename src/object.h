#ifndef PHYSINE_OBJECT_H_
#define PHYSINE_OBJECT_H_

#include <string>
#include <unordered_map>
#include <functional>

#include "collider.h"
#include "common.h"
#include "drawable.h"
#include "transform.h"
#include "utils.h"
#include "callback_list.h"

class Object {
    public:
        const std::string name;

        double mass;
        bool has_gravity = true;
        bool is_kinetic = true;
        Vector2f velocity;
        
        Transform* transform = nullptr;
        AbstractCollider* collider = nullptr;
        Drawable* drawable = nullptr;

        Object() = delete;
        Object(const std::string& name) : name{name}, mass{0.} {
            transform = new Transform();
        }
        Object(const std::string& name, Transform* transform) :
            name{name}, transform{transform} {}

        void add_collider(AbstractCollider* c) { collider = c; }
        void add_property(const std::string& key, const std::string& value) {
            custom_properties_[key] = value; 
        }

        std::string get_property(const std::string& key) {
            if (map_contains(custom_properties_, key)) return custom_properties_[key];
            return "";
        }

        void add_collision_listener(const std::function<void(Object*)>& collision_listener) {
            collision_listeners_.add_callback(collision_listener);
        }

        void collision_happened(Object* other) const { collision_listeners_.execute_all(other); }

        bool is_drawable() const { return drawable != nullptr; }

        ~Object() {
            delete transform;
            if (collider != nullptr)
                delete collider;
            if (drawable != nullptr)
                delete drawable;
        }
    
    private:
        std::unordered_map<std::string, std::string> custom_properties_;
        CallbackList<Object*> collision_listeners_;
};

#endif
