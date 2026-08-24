#include "MyBall.h"
#include <cstdlib>
#include <GL/gl.h>
#include <iostream>
#include <algorithm>

using namespace std;
namespace pba
{
    MyBall::MyBall(const std::string nam) : PbaThingyDingy(nam)
    {
        Reset();
        std::cout << name << " MyBall \n";
    }

    MyBall::~MyBall() {}

    void MyBall::Init(const std::vector<std::string> &args)
    {
        restitution = 0.9f;
        stickiness = 0.1f;
    }

    void MyBall::Display()
    {
        glPointSize(4.0);
        glBegin(GL_POINTS);
        for (size_t i = 0; i < particles->nb(); i++)
        {
            const Vector &p = particles->pos(i);
            const Color &c = particles->color(i);
            glColor3f(c.red(), c.green(), c.blue());
            glVertex3f(p.X(), p.Y(), p.Z());
        }
        glEnd();
    }

    void MyBall::Keyboard(unsigned char key, int x, int y)
    {
        PbaThingyDingy::Keyboard(key, x, y);
        if (key == 'c')
        {
            restitution = restitution - 0.05f;
            cout << "Restitution decrement, now is: " << restitution << endl;
        }
        else if (key == 'C')
        {
            restitution = restitution + 0.05f;
            cout << "Restitution increment, now is: " << restitution << endl;
        }
        else if (key == 's')
        {
            stickiness = stickiness - 0.01f;
            cout << "Stickiness decrement, now is: " << stickiness << endl;
        }
        else if (key == 'S')
        {
            stickiness = stickiness + 0.01f;
            cout << "Stickiness increment, now is: " << stickiness << endl;
        }
    }

    void MyBall::solve()
    {
        if (solver)
        {
            solver->Execute(dt);
        }

        for (size_t i = 0; i < particles->nb(); i++)
        {
            CalculateCollisions(i);
        }
    }

    void MyBall::Reset()
    {
        InitCreateParticles();
    }

    void MyBall::InitCreateParticles()
    {
        if (!particles)
        {
            particles = std::make_shared<ParticleStateData>();
        }
        particles->clear();

        const int count = 1000;
        for (int i = 0; i < count; i++)
        {
            float x = (drand48() * 2.0 - 1.0) * border.X() * 0.9f;
            float y = (drand48() * 2.0 - 1.0) * border.Y() * 0.9f;
            float z = (drand48() * 2.0 - 1.0) * border.Z() * 0.9f;

            Vector vel((drand48() - 0.5) * 2.0, (drand48() - 0.5) * 2.0, (drand48() - 0.5) * 2.0);

            particles->add(Vector(x, y, z), vel, Color(0.2, 0.6, 1.0, 1.0));
        }
    }

    void MyBall::CalculateCollisions(size_t i)
    {
        Vector p = particles->pos(i);
        Vector v = particles->vel(i);

        const float radius = 0.05f;
        Vector b = border - Vector(radius, radius, radius);

        for (int axis = 0; axis < 3; ++axis)
        {
            if (p[axis] < -b[axis])
            {
                p[axis] = -b[axis];
                v[axis] = fabs(v[axis]) * restitution;
                v[axis] *= 1.2f;
            }
            else if (p[axis] > b[axis])
            {
                p[axis] = b[axis];
                v[axis] = -fabs(v[axis]) * restitution;
                v[axis] *= 1.2f;
            }
        }

        particles->set_pos(i, p);
        particles->set_vel(i, v);
    }

    PbaThing CreateMyBall()
    {
        return PbaThing(new MyBall());
    }
}