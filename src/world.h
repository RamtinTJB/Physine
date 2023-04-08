#ifndef PHYSINE_WORLD_H_
#define PHYSINE_WORLD_H_

#include <vector>
#include <unordered_map>

#include "object.h"
#include "common.h"
#include "clock.h"
#include "graphics.h"
#include "collision_solver.h"
#include "collision.h"
#include "callback_list.h"
#include "event_manager.h"

const Vector2f g {0, 1000};

class World {
    private:
        std::unordered_map<std::string, Object*> objects_map_;
        std::vector<Object*> objects_;
        std::vector<Collision> collisions_;
        std::vector<Solver*> solvers_;
        CallbackList<World*> update_callbacks_;
        EventManager event_manager_;

        bool running_ = true;

        double delta_time_;

        Clock clock;
        Graphics* graphics = nullptr;

        bool gravity_ = true;
        bool air_resistance_ = true;

        void apply_gravity_to_object(Object*) const;
        void apply_air_resistance_to_object(Object*) const;
        void update_object_position(Object*) const;
        void update_object_rotation(Object*) const;

        void apply_environmental_forces_on_object(Object*) const;
        void update_object_transform(Object*) const;

        void check_collision(Object* obj1, Object* obj2);
        void check_collisions();
        void solve_collisions();

        void draw_object(Object*) const;

        void step(Object*) const;
    
    public:
        World();

        void add_object(Object* obj);
        Object* get_object_by_name(const std::string&);
        void mainloop();

        void gravity(bool gravity) { gravity_ = gravity; }
        bool gravity() const { return gravity_; }

        void air_resistance(bool air_resistance) { air_resistance_ = air_resistance; }
        bool air_resistance() const { return air_resistance_; }

        void add_update_callback(const std::function<void(World*)>& func) {
            update_callbacks_.add_callback(func);
        }

        void add_event_listener(EventType, std::function<void(Event)>);

        double get_delta_time() const { return delta_time_; }

        void close();

        ~World();
};

#endif
