#ifndef PHYSINE_COLLISION_H_
#define PHYSINE_COLLISION_H_

#include "object.h"

struct Collision {
    Object *obj1 = nullptr;
    Object *obj2 = nullptr;

    Collision() = default; 
    Collision(Object* obj1, Object* obj2) : obj1{obj1}, obj2{obj2} {}
};

#endif
