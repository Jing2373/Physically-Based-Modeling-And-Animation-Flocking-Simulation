#pragma once
#include "Vector.h"
#include "Color.h"
#include "PbaThing.h"

using namespace std;

namespace pba
{
    class MyScene : public PbaThingyDingy
    {
    public:
        MyScene(const std::string nam = "Triangulated Colored Floor");
        ~MyScene();

        void Init(const std::vector<std::string> &args);
        void Display();
        void Reset();

        void SetSceneSize(Vector size) { border = size; }

    private:
        Vector border;
    };

    pba::PbaThing CreateMyScene();
}
