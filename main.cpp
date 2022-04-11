#include <iostream>
#include <cmath>
#include <vector>

#include "cimg.h"
#include "world.h"

using namespace std;

using namespace cimg_library;
typedef unsigned char BYTE;

int main()
{
    World world;
    world.init_camera(60, 10, 640, 480, vec3(20, 40, 80), vec3(0, 0, 0), vec3(0, 1, 0));
    world.set_light(vec3(35, 35, 50), vec3(1, 1, 1));

    Sphere *sphere1 = new Sphere;
    sphere1->center = vec3(-30, 20, 10);
    sphere1->radius = 20;
    sphere1->color = vec3(0.2, 0.4, 1);
    sphere1->kd = 0.8;
    sphere1->ke = 0.9;
    sphere1->n = 4;

    world.add_object(sphere1);

    Sphere *sphere2 = new Sphere;
    sphere2->center = vec3(30, 20, 20);
    sphere2->radius = 15;
    sphere2->color = vec3(1, 1, 0);
    sphere2->kd = 0.8;
    sphere2->ke = 0.4;
    sphere2->n = 6;

    world.add_object(sphere2);

    Plane *plane = new Plane;
    plane->n = vec3(1, 10, 1);
    plane->n.normalize();
    plane->d = 0;
    plane->color = vec3(0.5, 0.5, 0.5);
    plane->kd = 0.9;
    plane->ke = 0;

    world.add_object(plane);

    Cylinder *cylinder1 = new Cylinder;
    cylinder1->pb = vec3(0, 20, 0);
    cylinder1->pa = vec3(0, 0, 0);
    cylinder1->radius = 10;
    cylinder1->color = vec3(1, 0, 0);
    cylinder1->kd = 0.8;
    cylinder1->ke = 0.5;
    sphere2->n = 16;

    world.add_object(cylinder1);

    world.render();
}