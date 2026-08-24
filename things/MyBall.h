#pragma once
#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"
#include "ParticleState.h"
#include "Solver.h"

namespace pba
{
    using SolverPtr = std::shared_ptr<Solver>;

    class MyBall : public PbaThingyDingy
    {
    public:
        MyBall(const std::string nam = "Ball");
        ~MyBall();

        void Init(const std::vector<std::string> &args);
        void Display();
        void Keyboard(unsigned char key, int x, int y);
        void solve();
        void Reset();

        void SetSolver(SolverPtr in_solver) { solver = in_solver; }
        ParticleState GetParticles() const { return particles; }
        void SetSceneSize(Vector size) { border = size; }

    private:
        void InitCreateParticles();
        void CalculateCollisions(size_t i);

        Vector border;
        float restitution;
        float stickiness;

        ParticleState particles;
        SolverPtr solver;
    };

    pba::PbaThing CreateMyBall();
}