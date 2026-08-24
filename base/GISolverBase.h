#pragma once
#include <memory>

namespace pba
{
   class GISolverBase
   {
   public:
      virtual void init() = 0;
      virtual void solve(const double dt) = 0;
      virtual ~GISolverBase() {};
   };

   using GISolver = std::shared_ptr<GISolverBase>;
}
