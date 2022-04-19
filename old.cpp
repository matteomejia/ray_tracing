#include <iostream>
#include <cmath>
#include <vector>

#include "cimg.h"
#include "world.h"
#include "camera.h"
#include "object.h"
#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"

using namespace cimg_library;
typedef unsigned char BYTE;

int main()
{
    World world;

    Camera *camera = new Camera;
    camera->init(60, 10, 640, 480, vec3(20, 40, 80), vec3(0, 0, 0), vec3(0, 1, 0));
    camera->calcular_vectores();

    world.add_camera(camera);

    Light *light1 = new Light;
    light1->color = vec3(1, 1, 1);
    light1->pos = vec3(35, 35, 50);

    world.add_light(light1);

    // Light *light2 = new Light;
    // light2->color = vec3(1, 1, 1);
    // light2->pos = vec3(-35, 35, -50);

    // world.add_light(light2);

    Sphere *sphere1 = new Sphere;
    sphere1->center = vec3(-30, 20, 10);
    sphere1->radius = 20;
    sphere1->color = vec3(1, 0, 1);
    sphere1->kd = 0.8;
    sphere1->ke = 0.9;
    sphere1->ks = 4;

    world.add_object(sphere1);

    Sphere *sphere2 = new Sphere;
    sphere2->center = vec3(30, 20, 20);
    sphere2->radius = 15;
    sphere2->color = vec3(1, 1, 0);
    sphere2->kd = 0.8;
    sphere2->ke = 0.4;
    sphere2->ks = 16;
    sphere2->ior = 2;
    // sphere2->ks = 6;

    world.add_object(sphere2);

    Sphere *sphere3 = new Sphere;
    sphere3->center = vec3(30, 20, 20);
    sphere3->radius = 4;
    sphere3->color = vec3(0, 0, 1);
    sphere3->kd = 0.8;
    sphere3->ke = 0.4;
    sphere3->ks = 16;

    world.add_object(sphere3);

    Plane *plane = new Plane;
    plane->n = vec3(1, 10, 1);
    plane->n.normalize();
    plane->d = 0;
    plane->color = vec3(0.5, 0.5, 0.5);
    plane->kd = 0.9;
    plane->ke = 0;

    world.add_object(plane);

    Cylinder *cylinder1 = new Cylinder;
    cylinder1->pb = vec3(0, 20, 20);
    cylinder1->pa = vec3(0, 0, 20);
    cylinder1->radius = 10;
    cylinder1->color = vec3(0, 1, 1);
    cylinder1->ke = 0;
    cylinder1->ior = 1.5;

    world.add_object(cylinder1);

    Sphere *sphere4 = new Sphere;
    sphere4->center = vec3(0, 10, 20);
    sphere4->radius = 4;
    sphere4->color = vec3(1, 1, 1);
    sphere4->kd = 0.9;
    sphere4->ke = 0.9;
    sphere4->ks = 16;

    world.add_object(sphere4);

    world.render();
}