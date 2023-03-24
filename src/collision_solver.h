#ifndef COLLISION_SOLVER_H_
#define COLLISION_SOLVER_H_

#include "object.h"
#include "vector.h"
#include "collision.h"

class Solver {
    public:
        virtual void solve(const Collision& collision) const = 0;
        virtual ~Solver() = default;
};

class VelocitySolver : public Solver {
    public:
        void solve(const Collision& collision) const override;
};

class PositionSolver : public Solver {
    public:
        void solve(const Collision& collision) const override;
};

#endif
