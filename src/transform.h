#ifndef PHYSINE_TRANSFORM_H_
#define PHYSINE_TRANSFORM_H_

#include "common.h"

struct Transform {
    Vector2f position;
    Vector2f scale {1, 1};
    Vector2f rotation;
};

#endif
