#ifndef COLLISION_SOLVER_H_
#define COLLISION_SOLVER_H_

#include "object.h"
#include "vector.h"
#include "collision.h"

class Solver {
    public:
        void solve(const Collision& collision) const;
};

#endif
