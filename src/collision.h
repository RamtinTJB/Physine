#ifndef PHYSINE_COLLISION_H_
#define PHYSINE_COLLISION_H_

#include "object.h"
#include "collision_points.h"

struct Collision {
    Object *obj1 = nullptr;
    Object *obj2 = nullptr;
    CollisionPoints points;

    Collision() = default; 
    Collision(Object* obj1, Object* obj2, CollisionPoints col) : obj1{obj1}, obj2{obj2}, points{col} {}
};

#endif
