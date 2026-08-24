#pragma once
#include "PbaThing.h"
#include "ParticleState.h"
#include "GISolverBase.h"

namespace pba
{
    class Solver : public PbaThingyDingy
    {
    public:
        Solver(const std::string nam = "Solver");

        void Init(const std::vector<std::string> &args);
        void Execute(double dt);
        void SetParticles(ParticleState s) { particles = s; }

    private:
        GISolver solver;
        ParticleState particles;
    };

    pba::PbaThing CreateSolver();
}