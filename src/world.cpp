#include "world.h"
#include "utils.h"

#include <iostream>
#include <thread>
#include <chrono>

World::World() {
    clock.restart();
    graphics = new Graphics(1500, 1500);
    solvers_.push_back(new PositionSolver());
    solvers_.push_back(new ObjectAtRestSolver());
    solvers_.push_back(new VelocitySolver());
}

void World::add_air_resistance(Object* obj, double dt) {
    obj->velocity -= (0.5*0.05*dt/obj->mass)*obj->velocity.dot(obj->velocity)*obj->velocity.unit();
}

void World::update_velocities(double dt) {
    for (Object* obj : objects_) {
        if (!obj->is_kinetic) continue;
        if (obj->has_gravity && gravity_) {
            obj->velocity += g*dt;
        }
        if (air_resistance_) {
            add_air_resistance(obj, dt);
        }
    }
}

void World::update_transforms(double dt) {
    for (Object* obj : objects_) {
        if (!obj->is_kinetic) continue;
        obj->transform->position += obj->velocity * dt;
        obj->transform->rotation += obj->angular_velocity * dt;
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
        obj1->collision_happened(obj2);
        obj2->collision_happened(obj1);
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

void World::add_object(Object* obj) {
    if (map_contains(objects_map_, obj->name)) throw std::invalid_argument("Duplicate object name not allowed");
    objects_.push_back(obj);
    objects_map_[obj->name] = obj;
}

Object* World::get_object_by_name(const std::string& name) {
    if (map_contains(objects_map_, name)) return objects_map_[name];
    return nullptr;
}

void World::add_event_listener(EventType type, const std::function<void(Event)>& listener) {
    event_manager_.add_listener(type, listener);
}

void World::mainloop() {
    clock.restart();
    while (true) {
        if (event_manager_.has_closed()) return;
        delta_time_ = clock.delta_time();
        clock.restart();

        update_velocities(delta_time_);
        update_transforms(delta_time_);
        check_collisions();
        solve_collisions();

        draw_objects();
        graphics->draw_objects(objects_);
        event_manager_.check_events(*graphics->get_window());
        update_callbacks_.execute_all(this);
    }
    graphics->close();
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
