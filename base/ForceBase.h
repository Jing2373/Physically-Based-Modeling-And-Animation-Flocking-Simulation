#pragma once
#include <memory>
#include "ParticleState.h"

namespace pba
{
   class ForceBase
   {
   public:
      ForceBase() {};
      virtual void compute(ParticleState &p, const double dt) = 0;
      virtual ~ForceBase() {};
   };

   typedef std::shared_ptr<ForceBase> Force;

}