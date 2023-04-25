#include "world.h"
#include "utils.h"

#include <iostream>
#include <thread>
#include <chrono>

World::World(int width, int height) {
    clock.restart();
    init_graphics(width, height);
    solvers_.push_back(new PositionSolver());
    solvers_.push_back(new ObjectAtRestSolver());
    solvers_.push_back(new VelocitySolver());
}

void World::init_graphics(int width, int height) {
    graphics = new Graphics(width, height);
}

void World::apply_gravity_to_object(Object* obj) const {
    if (obj->has_gravity && gravity_) {
        obj->velocity += g * delta_time_;
    }
}

void World::apply_air_resistance_to_object(Object* obj) const {
    if (air_resistance_) {
        obj->velocity -= (0.5*0.05*delta_time_/obj->mass) * obj->velocity.dot(obj->velocity)*obj->velocity.unit();
    }
}

void World::update_object_position(Object* obj) const {
    if (obj->is_kinetic){
        obj->transform->position += obj->velocity * delta_time_;
    }
}

void World::update_object_rotation(Object* obj) const {
    if (obj->is_kinetic) {
        obj->transform->rotation += obj->angular_velocity * delta_time_;
    }
}

void World::apply_environmental_forces_on_object(Object* obj) const {
    if (obj->is_kinetic) {
        apply_gravity_to_object(obj);
        apply_air_resistance_to_object(obj);
    }
}

void World::update_object_transform(Object* obj) const {
    update_object_position(obj);
    update_object_rotation(obj);
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
    for (size_t i = 0; i < objects_.size(); ++i) {
        for (size_t j = i; j < objects_.size(); ++j) {
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

void World::draw_object(Object* obj) const {
    if (obj->is_drawable()) {
        obj->drawable->render(obj->transform);
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

void World::add_event_listener(EventType type, std::function<void(Event)> listener) {
    event_manager_.add_listener(type, listener);
}

void World::step(Object* obj) const {
    apply_environmental_forces_on_object(obj);
    update_object_transform(obj);
    draw_object(obj);
    graphics->draw_object(obj);
}

void World::mainloop() {
    clock.restart();
    while (running_) {
        delta_time_ = clock.delta_time();
        clock.restart();
        graphics->clear_window();

        for (Object* obj : objects_) {
            step(obj);
        }

        graphics->display();

        check_collisions();
        solve_collisions();

        event_manager_.check_events(*graphics->get_window());
        update_callbacks_.execute_all(this);
    }
}

void World::close() {
    running_ = false;
    graphics->close();
}

void World::exit_on_close() {
    add_event_listener(EventType::Closed, [this]([[maybe_unused]] Event e) { this->close(); });
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
