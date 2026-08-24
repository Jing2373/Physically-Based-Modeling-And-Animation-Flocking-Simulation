#include "DrivingBehaviors.h"
#include <cstdlib>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "Limiter.h"

using namespace std;

namespace pba
{

   DrivingBehaviors::DrivingBehaviors(const string nam) : PbaThingyDingy(nam)
   {
      std::cout << name << " constructed\n";
   }

   DrivingBehaviors::~DrivingBehaviors() {}

   void DrivingBehaviors::Init(const vector<string> &args)
   {
      kC = 5.0f;
      kM = 1.5f;
      kCA = 0.5f;

      R = 2.0f;
      R_amp = 1.0f;

      init_Theta = 80.0f;
      init_Theta_amp = 20.0f;

      A_budget = 15.0f;

      cosTheta = cos(init_Theta * M_PI / 180.0f);
      cosThetaAmp = cos((init_Theta + init_Theta_amp) * M_PI / 180.0f);
   }

   void DrivingBehaviors::Keyboard(unsigned char key, int x, int y)
   {
      PbaThingyDingy::Keyboard(key, x, y);

      // Implement keys to decrease/increase the parameters in each of the three behaviors.
      // Centering
      if (key == 'k')
      {
         kC -= 0.1f;
         cout << "Centering decrement, now is: " << kC << endl;
      }
      else if (key == 'K')
      {
         kC += 0.1f;
         cout << "Centering increment, now is: " << kC << endl;
      }
      // Velocity Matching
      else if (key == 'm')
      {
         kM -= 0.1f;
         cout << "Velocity Matching decrement, now is: " << kM << endl;
      }
      else if (key == 'M')
      {
         kM += 0.1f;
         cout << "Velocity Matching increment, now is: " << kM << endl;
      }
      // Collision Avoidance
      else if (key == 'a')
      {
         kCA -= 0.1f;
         cout << "Collision Avoidance decrement, now is: " << kCA << endl;
      }
      else if (key == 'A')
      {
         kCA += 0.1f;
         cout << "Collision Avoidance increment, now is: " << kCA << endl;
      }
   }

   void DrivingBehaviors::solve()
   {
      const float dt = 0.05f;

      static int leader = 0;
      static float last_change_time = 0.0f;

      float current_time = glutGet(GLUT_ELAPSED_TIME) * 0.001f;

      static Vector directions[4] = {
          Vector(1, 1, 0),
          Vector(1, -1, 0),
          Vector(-1, 1, 0),
          Vector(-1, -1, 0)};

      static int dir_idx = 0;

      if (current_time - last_change_time > 10.0f)
      {
         particles->set_color(leader, Color(0.2, 0.6, 1.0, 1.0));
         leader = rand() % particles->nb();
         dir_idx = rand() % 4;
         last_change_time = current_time;
         particles->set_color(leader, Color(1.0, 0.0, 0.0, 1.0));
      }

      Vector leader_dir = directions[dir_idx];
      leader_dir.normalize();

      for (size_t i = 0; i < particles->nb(); i++)
      {
         // leader
         if ((int)i == leader)
         {
            Vector v = particles->vel(i);

            if (v.magnitude() < 0.1f)
            {
               v = leader_dir;
            }
            v.normalize();
            particles->set_vel(i, v * 3.0f);

            continue;
         }

         // others
         Vector acc = computeAcceleration(i, particles.get());

         Vector leader_pos = particles->pos(leader);
         Vector leader_v = particles->vel(leader);
         float mag = leader_v.magnitude();

         if (mag > 1e-6f)
         {
            Vector dir = leader_v / mag;
            Vector target_pos = leader_pos - dir * 1.5f;
            Vector to_target = target_pos - particles->pos(i);
            float dist_to_target = to_target.magnitude();

            if (dist_to_target > 1e-6f)
            {
               acc += dir * 4.0f;
               acc += (to_target / dist_to_target) * 5.0f;
            }
         }

         Vector v = particles->vel(i) + acc * dt;

         v *= 0.95f;

         float speed = v.magnitude();

         if (speed < 1.0f && speed > 0.001)
         {
            v *= (1.0f / speed);
         }
         if (speed > 3.5f)
         {
            v *= (3.5f / speed);
         }

         particles->set_vel(i, v);
      }
   }
   void DrivingBehaviors::Reset() {}

   Vector DrivingBehaviors::computeAcceleration(int i, ParticleStateData *PQ)
   {
      double residual = A_budget;
      Vector acc(0, 0, 0);

      // Collision Avoidance
      Vector ca = computeCollisionAvoidance(i, PQ);
      double ca_mag = ca.magnitude();

      if (ca_mag < residual)
      {
         acc += ca;
         residual -= ca_mag;
      }
      else
      {
         return ca * (residual / ca_mag);
      }

      // Velocity Matching
      Vector vm = computeVelocityMatching(i, PQ);
      double vm_mag = vm.magnitude();

      if (vm_mag < residual)
      {
         acc += vm;
         residual -= vm_mag;
      }
      else
      {
         acc += vm * (residual / vm_mag);
         return acc;
      }

      // Centering
      Vector c = computeCentering(i, PQ);
      double c_mag = c.magnitude();

      if (c_mag < residual)
      {
         acc += c;
      }
      else
      {
         acc += c * (residual / c_mag);
      }

      return acc;
   }

   Vector DrivingBehaviors::computeCentering(int i, ParticleStateData *PQ)
   {
      Vector acc(0, 0, 0);
      Vector xi = PQ->pos(i);
      Vector vi = PQ->vel(i);

      for (int j = 0; j < (int)PQ->nb(); ++j)
      {
         if (i == j)
         {
            continue;
         }

         Vector dx_ab = PQ->pos(j) - xi;
         float d = dx_ab.magnitude();

         float r_ab = getRangeLimiter(d, R, R_amp);
         float f_ab = getFOVLimiter(dx_ab, vi, cosTheta, cosThetaAmp);

         acc += dx_ab * r_ab * f_ab;
      }
      return acc * kC;
   }

   Vector DrivingBehaviors::computeVelocityMatching(int i, ParticleStateData *PQ)
   {
      Vector acc(0, 0, 0);
      Vector xi = PQ->pos(i);
      Vector vi = PQ->vel(i);

      for (int j = 0; j < (int)PQ->nb(); ++j)
      {
         if (i == j)
         {
            continue;
         }

         Vector dx_ab = PQ->pos(j) - xi;
         Vector dv_ab = PQ->vel(j) - vi;
         float d = dx_ab.magnitude();

         float r_ab = getRangeLimiter(d, R, R_amp);
         float f_ab = getFOVLimiter(dx_ab, vi, cosTheta, cosThetaAmp);

         acc += dv_ab * r_ab * f_ab;
      }
      return acc * kM;
   }

   Vector DrivingBehaviors::computeCollisionAvoidance(int i, ParticleStateData *PQ)
   {
      Vector acc(0, 0, 0);
      Vector xi = PQ->pos(i);
      Vector vi = PQ->vel(i);

      for (int j = 0; j < (int)PQ->nb(); ++j)
      {
         if (i == j)
         {
            continue;
         }

         Vector dx_ab = PQ->pos(j) - xi;
         float d2 = dx_ab.magnitude() * dx_ab.magnitude();
         d2 = std::max(d2, 0.3f);

         float d = sqrt(d2);
         float r_ab = getRangeLimiter(d, R, R_amp);
         float f_ab = getFOVLimiter(dx_ab, vi, cosTheta, cosThetaAmp);

         acc -= (dx_ab / d2) * r_ab * f_ab;
      }
      return acc * kCA;
   }

   PbaThing CreateDrivingBehaviors() { return PbaThing(new DrivingBehaviors()); }
}
