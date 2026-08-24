#pragma once
#include "GISolverBase.h"
#include "ParticleState.h"

namespace pba
{
    class AdvancePosition : public GISolverBase
    {
    public:
        AdvancePosition(ParticleState &pq);
        ~AdvancePosition() {}

        void init() override {}
        void solve(const double dt);

    private:
        ParticleState PQ;
    };

    GISolver make_advance_position(ParticleState pq);
}
