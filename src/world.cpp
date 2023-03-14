#include "world.h"

World::World() {
    clock.restart();
}

void World::update_velocities(double dt) {
    for (Object* obj : objects_) {
        obj->velocity += (1/obj->mass)*g*dt;
    }
}

void World::update_transforms(double dt) {
    for (Object* obj : objects_) {
        obj->transform->position += obj->velocity * dt;
    }
}

void World::mainloop() {
    while (true) {
        double dt = clock.delta_time();

        update_velocities(dt);
        update_transforms(dt);

        clock.restart();
    }
}
