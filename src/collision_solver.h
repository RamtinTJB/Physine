#ifndef COLLISION_SOLVER_H_
#define COLLISION_SOLVER_H_

#include "object.h"
#include "vector.h"

class Solver {
    public:
        void solve(Object* obj1, Object* obj2) const;
};

#endif
