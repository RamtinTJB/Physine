#ifndef PHYSINE_WORLD_H_
#define PHYSINE_WORLD_H_

#include <vector>

#include "object.h"
#include "common.h"
#include "clock.h"
#include "graphics.h"

const Vector2f g {0, 200};

class World {
    private:
        std::vector<Object*> objects_;
        Clock clock;
        Graphics* graphics = nullptr;

        bool gravity_ = true;

        void update_velocities(double dt);
        void update_transforms(double dt);

        void check_collisions();

        void draw_objects();
    
    public:
        World();

        void add_object(Object* obj) { objects_.push_back(obj); }
        void mainloop();

        void set_gravity(bool gravity) { gravity_ = gravity; }

        ~World();
};

#endif
