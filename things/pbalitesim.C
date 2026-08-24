
#include "PbaViewer.h"
#include "MyScene.h"
#include "MyBall.h"
#include "DrivingBehaviors.h"
#include "Solver.h"
#include "SetupScene.h"

int main(int argc, char **argv)
{
   std::vector<std::string> args;
   for (int i = 0; i < argc; i++)
   {
      args.push_back(argv[i]);
   }

   pba::PbaViewer *viewer = pba::CreateViewer();

   // Solver
   pba::PbaThing solver = pba::CreateSolver();
   auto solver_ptr = std::static_pointer_cast<pba::Solver>(solver);
   viewer->AddThing(solver);

   // DrivingBehaviors
   pba::PbaThing behaviors = pba::CreateDrivingBehaviors();
   auto behaviors_ptr = std::static_pointer_cast<pba::DrivingBehaviors>(behaviors);
   viewer->AddThing(behaviors);

   // Scene
   pba::PbaThing myscene = pba::CreateMyScene();
   viewer->AddThing(myscene);

   // MyBall
   pba::PbaThing myball = pba::CreateMyBall();
   auto myball_ptr = std::static_pointer_cast<pba::MyBall>(myball);
   myball_ptr->SetSolver(solver_ptr);
   behaviors_ptr->SetParticles(myball_ptr->GetParticles());
   solver_ptr->SetParticles(myball_ptr->GetParticles());
   viewer->AddThing(myball);

   // Setup Scene
   pba::SetupScene setupScene;
   setupScene.Setup(myball, myscene);

   viewer->Init(args);
   viewer->MainLoop();
}
