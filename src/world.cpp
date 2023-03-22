#include "world.h"

#include <iostream>
#include <thread>
#include <chrono>

World::World() {
    clock.restart();
    graphics = new Graphics(1500, 1500);
    solvers_.push_back(new VelocitySolver());
}

void World::update_velocities(double dt) {
    for (Object* obj : objects_) {
        if (obj->has_gravity && obj->is_kinetic)
            obj->velocity += g*dt;
    }
}

void World::update_transforms(double dt) {
    for (Object* obj : objects_) {
        if (obj->is_kinetic)
            obj->transform->position += obj->velocity * dt;
    }
}

void World::check_collision(Object* obj1, Object* obj2) {
    if (obj1->collider == nullptr || obj2->collider == nullptr) return;
    CollisionPoints col_pts;
    if (obj2->collider->get_type() == ColliderType::CIRCLE) {
        col_pts = obj1->collider->test_collision(dynamic_cast<CircleCollider*>(obj2->collider));
    } else if (obj2->collider->get_type() == ColliderType::BOX) {
        col_pts = obj1->collider->test_collision(dynamic_cast<BoxCollider*>(obj2->collider));
    }
    if (col_pts.has_collision) {
        collisions_.push_back(Collision(obj1, obj2, col_pts));
    }
}

void World::check_collisions() {
    for (int i = 0; i < objects_.size(); ++i) {
        for (int j = i; j < objects_.size(); ++j) {
            Object* obj1 = objects_[i];
            Object* obj2 = objects_[j];
            if (obj1 == obj2) continue;
            check_collision(obj1, obj2);
        }
    }
}

void World::solve_collisions() {
    for (Collision c : collisions_) {
        for (Solver* solver: solvers_) {
            solver->solve(c);
        }
    }
    collisions_.clear();
}

void World::draw_objects() {
    for (Object* obj: objects_) {
        if (obj->is_drawable()) {
            obj->drawable->render(obj->transform);
        }
    }
}

void World::mainloop() {
    clock.restart();
    while (true) {
        if (graphics->has_closed()) return;
        double dt = clock.delta_time();
        clock.restart();

        update_velocities(dt);
        update_transforms(dt);
        check_collisions();
        solve_collisions();

        draw_objects();
        graphics->draw_objects(objects_);
    }
}

World::~World() {
    for (Object* obj : objects_) {
        delete obj;
    }
    if (graphics != nullptr) delete graphics;
    for (Solver* solver: solvers_) {
        delete solver;
    }
}
