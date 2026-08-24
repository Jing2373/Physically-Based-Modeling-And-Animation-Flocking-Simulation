#include "MyScene.h"
#include <cstdlib>
#include <GL/gl.h>   // OpenGL itself.
#include <GL/glu.h>  // GLU support library.
#include <GL/glut.h> // GLUT support library.
#include <iostream>

using namespace std;
using namespace pba;

MyScene::MyScene(const std::string nam) : PbaThingyDingy(nam)
{
   Reset();
   std::cout << name << " constructed\n";
}

MyScene::~MyScene() {}

void MyScene::Init(const std::vector<std::string> &args) {}

void MyScene::Display()
{
   float bx = border.X();
   float by = border.Y();
   float bz = border.Z();

   glBegin(GL_TRIANGLES);
   glColor3f(0.7, 0.9, 1.0);
   glVertex3f(-bx, by, -bz);
   glVertex3f(-bx, -by, -bz);
   glVertex3f(bx, by, -bz);

   glColor3f(0.8, 0.95, 1.0);
   glVertex3f(bx, -by, -bz);
   glVertex3f(bx, by, -bz);
   glVertex3f(-bx, -by, -bz);
   glEnd();

   // top
   glBegin(GL_TRIANGLES);
   glColor3f(1.0, 1.0, 0.6);
   glVertex3f(-bx, by, bz);
   glVertex3f(bx, by, bz);
   glVertex3f(-bx, by, -bz);

   glColor3f(1.0, 1.0, 0.8);
   glVertex3f(bx, by, bz);
   glVertex3f(bx, by, -bz);
   glVertex3f(-bx, by, -bz);
   glEnd();

   // bottom
   glBegin(GL_TRIANGLES);
   glColor3f(1.0, 0.7, 0.8);
   glVertex3f(-bx, -by, -bz);
   glVertex3f(-bx, -by, bz);
   glVertex3f(bx, -by, -bz);

   glColor3f(1.0, 0.8, 0.9);
   glVertex3f(bx, -by, bz);
   glVertex3f(bx, -by, -bz);
   glVertex3f(-bx, -by, bz);
   glEnd();

   // left
   glBegin(GL_TRIANGLES);
   glColor3f(0.7, 1.0, 0.7);
   glVertex3f(-bx, by, -bz);
   glVertex3f(-bx, -by, -bz);
   glVertex3f(-bx, by, bz);

   glColor3f(0.85, 1.0, 0.85);
   glVertex3f(-bx, -by, bz);
   glVertex3f(-bx, -by, -bz);
   glVertex3f(-bx, by, bz);
   glEnd();

   // right
   glBegin(GL_TRIANGLES);
   glColor3f(0.8, 0.7, 1.0);
   glVertex3f(bx, by, -bz);
   glVertex3f(bx, -by, -bz);
   glVertex3f(bx, by, bz);

   glColor3f(0.9, 0.85, 1.0);
   glVertex3f(bx, -by, bz);
   glVertex3f(bx, -by, -bz);
   glVertex3f(bx, by, bz);
   glEnd();
}

void MyScene::Reset()
{
}

pba::PbaThing pba::CreateMyScene()
{
   return PbaThing(new MyScene());
}
