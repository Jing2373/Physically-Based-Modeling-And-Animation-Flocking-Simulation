#include "SetupScene.h"
#include "MyBall.h"
#include "MyScene.h"
#include <fstream>
#include <sstream>

namespace pba
{
    using std::vector;
    void SetupScene::Setup(pba::PbaThing ball, pba::PbaThing scene)
    {
        pba::Vector border(5.0, 5.0, 5.0);
        // Scene
        auto scene_ptr = static_pointer_cast<pba::MyScene>(scene);
        scene_ptr->SetSceneSize(border);

        // Particals
        auto ball_ptr = static_pointer_cast<pba::MyBall>(ball);
        ball_ptr->SetSceneSize(border);
    }
}