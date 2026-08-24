#include "Vector.h"
#include "PbaThing.h"

namespace pba
{

    class SetupScene
    {
    public:
        SetupScene() = default;

        void Setup(pba::PbaThing ball, pba::PbaThing scene);
    };

}