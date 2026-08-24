#pragma once
#include <string>
#include <vector>
#include "Vector.h"
#include "PbaThing.h"
#include "ParticleState.h"

namespace pba
{
    class DrivingBehaviors : public PbaThingyDingy
    {
    public:
        DrivingBehaviors(const std::string nam = "Three Driving Behaviors");
        ~DrivingBehaviors();

        void Init(const std::vector<std::string> &args);
        void Keyboard(unsigned char key, int x, int y);
        void Reset();
        void solve();

        void SetParticles(ParticleState p) { particles = p; }
        Vector computeAcceleration(int i, ParticleStateData *PQ);

        void setCentering(float value) { kC = value; }
        void setVelocityMatching(float value) { kM = value; }
        void setCollisionAvoidance(float value) { kCA = value; }

    private:
        ParticleState particles;

        float kC = 1.0f;
        float kM = 1.0f;
        float kCA = 1.0f;

        float init_Theta = 60.0f;
        float init_Theta_amp = 20.0f;

        float cosTheta = 1.0f;
        float cosThetaAmp = 1.0f;

        float R = 5.0f;
        float R_amp = 2.0f;

        float A_budget = 20.0f;

        Vector computeCentering(int i, ParticleStateData *PQ);
        Vector computeVelocityMatching(int i, ParticleStateData *PQ);
        Vector computeCollisionAvoidance(int i, ParticleStateData *PQ);
    };

    pba::PbaThing CreateDrivingBehaviors();
}