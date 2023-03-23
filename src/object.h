#ifndef PHYSINE_OBJECT_H_
#define PHYSINE_OBJECT_H_

#include <string>
#include <unordered_map>

#include "collider.h"
#include "common.h"
#include "drawable.h"
#include "transform.h"
#include "utils.h"

class Object {
    public:
        const std::string name;

        double mass;
        bool has_gravity = true;
        bool is_kinetic = true;
        Vector2f velocity;
        
        Transform* transform = nullptr;
        Collider* collider = nullptr;
        Drawable* drawable = nullptr;

        Object() = delete;
        Object(const std::string& name) : name{name}, mass{0.} {
            transform = new Transform();
        }

        void add_collider(Collider* c) { collider = c; }
        void add_property(const std::string& key, const std::string& value) {
            custom_properties_[key] = value; 
        }

        std::string get_property(const std::string& key) {
            if (map_contains(custom_properties_, key)) return custom_properties_[key];
            return "";
        }

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
};

#endif
