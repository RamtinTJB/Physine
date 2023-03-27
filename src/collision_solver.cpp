#include <iostream>

#include "collision_solver.h"
#include "debug.h"

void VelocitySolver::solve(const Collision& collision) const {
    Object* obj1 = collision.obj1;
    Object* obj2 = collision.obj2;
    double total_mass = obj1->mass + obj2->mass;
    Vector2f delta_x = collision.points.normal;
    Vector2f delta_v = obj2->velocity - obj1->velocity;

    double mass_fraction1 = 0, mass_fraction2 = 0;

    if (!obj2->is_kinetic) {
        mass_fraction1 = 2;
    } else {
        mass_fraction1 = 2*obj2->mass/total_mass;
    }
    if (!obj1->is_kinetic) {
        mass_fraction2 = 2;
    } else {
        mass_fraction2 = 2*obj1->mass/total_mass;
    }

    Vector2f v1 = obj1->velocity - mass_fraction1*(delta_v.dot(delta_x)/
            (delta_x.magnitude()*delta_x.magnitude()))*delta_x.opposite();

    Vector2f v2 = obj2->velocity - mass_fraction2*(delta_v.dot(delta_x)/
            (delta_x.magnitude()*delta_x.magnitude()))*delta_x;
    
    if (obj1->is_kinetic)
        obj1->velocity = v1*0.9;
    if (obj2->is_kinetic)
        obj2->velocity = v2*0.9;
}

void PositionSolver::solve(const Collision& collision) const {
    Object* obj1 = collision.obj1;
    Object* obj2 = collision.obj2;
    Vector2f normal = collision.points.overlap_length*collision.points.normal.unit();
    
    if (!obj1->is_kinetic) {
        obj2->transform->position += normal;
    } else if (!obj2->is_kinetic) {
        obj1->transform->position += normal.opposite();
    } else {
        obj1->transform->position += -0.5*normal;
        obj2->transform->position += 0.5*normal;
    }
}
