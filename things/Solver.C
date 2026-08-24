#include "Solver.h"
#include "AdvancePosition.h"

namespace pba
{
   Solver::Solver(const std::string nam) : PbaThingyDingy(nam) {}

   void Solver::Init(const std::vector<std::string> &args)
   {
      if (particles)
      {
         solver = std::make_shared<AdvancePosition>(particles);
      }
   }

   void Solver::Execute(const double dt)
   {
      if (solver)
         solver->solve(dt);
   }

   PbaThing CreateSolver() { return PbaThing(new Solver()); }
}