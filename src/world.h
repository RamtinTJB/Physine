#ifndef PHYSINE_WORLD_H_
#define PHYSINE_WORLD_H_

#include <vector>

#include "object.h"
#include "common.h"
#include "clock.h"

const Vector2f g {0, -9.81};

class World {
    private:
        std::vector<Object*> objects_;
        Clock clock;

        void update_velocities(double dt);
        void update_transforms(double dt);
    
    public:
        World();
        void add_object(Object* obj) { objects_.push_back(obj); }
        void mainloop();
};

#endif
