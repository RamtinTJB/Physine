#include "world.h"
#include <iostream>

World::World() {
    clock.restart();
    graphics = new Graphics(1500, 1500);
}

void World::update_velocities(double dt) {
    for (Object* obj : objects_) {
        if (gravity_)
            obj->velocity += g*dt;
    }
}

void World::update_transforms(double dt) {
    for (Object* obj : objects_) {
        obj->transform->position += obj->velocity * dt;
    }
}

void World::check_collisions() {
    for (Object* obj1 : objects_) {
        for (Object* obj2 : objects_) {
            if (obj1 == obj2) continue;
            if (obj1->collider != nullptr && obj2->collider != nullptr) {
                if (obj1->collider->test_collision(dynamic_cast<CircleCollider*>(obj2->collider))) {
                    // TODO Resolve Collision
                    obj1->velocity = Vector2f{-obj1->velocity[0], -obj1->velocity[1]};
                }
            }
        }
    }
}

void World::draw_objects() {
    for (Object* obj: objects_) {
        if (obj->is_drawable()) {
            obj->drawable->render(obj->transform);
        }
    }
}

void World::mainloop() {
    while (true) {
        if (graphics->has_closed()) return;
        double dt = clock.delta_time();
        clock.restart();

        update_velocities(dt);
        update_transforms(dt);
        check_collisions();

        draw_objects();
        graphics->draw_objects(objects_);
    }
}

World::~World() {
    for (Object* obj : objects_) {
        delete obj;
    }
}
