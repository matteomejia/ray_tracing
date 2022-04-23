#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>

#include "cimg.h"
#include "world.h"
#include "camera.h"
#include "object.h"
#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "cylinder.h"

int main(int argc, char **argv)
{
    World world;

    int camera_x = -30; // -30 a 30
    int camera_z = 30;
    int fire_x = 5; // 5 a -5
    int fire_y = 5; // 5 a -5

    // int camera_x = std::atoi(argv[1]);
    // int camera_z = std::atoi(argv[2]);
    // int fire_x = std::atoi(argv[3]);
    // int fire_y = std::atoi(argv[4]);

    vec3 lookfrom(camera_x, 30, camera_z);
    vec3 lookat(0, 10, 0);
    vec3 up(0, 1, 0);

    Camera *camera = new Camera;
    camera->init(60, 10, 640, 480, lookfrom, lookat, up);
    camera->calcular_vectores();

    world.add_camera(camera);

    Plane *plane = new Plane;
    plane->n = vec3(1, 10, 1);
    plane->n.normalize();
    plane->d = 0;
    plane->color = vec3(0.5, 0.5, 0.5);
    plane->kd = 0.9;
    plane->ke = 0;
    plane->kr = 0.5;

    world.add_object(plane);

    // Luz exterior

    Light *light = new Light;
    light->color = vec3(0.25, 0.25, 0.25);
    light->pos = vec3(100, 100, 100);

    world.add_light(light);

    // Frasco y Tapa

    Cylinder *cylinder_outer = new Cylinder;
    cylinder_outer->color = vec3(0.25f, 0.25f, 0.25f);
    cylinder_outer->pa = vec3(0, 20, 0);
    cylinder_outer->pb = vec3(0, 0, 0);
    cylinder_outer->radius = 12;
    cylinder_outer->ior = 1;

    Cylinder *cylinder_inner = new Cylinder;
    cylinder_inner->color = vec3(0.25f, 0.25f, 0.25f);
    cylinder_inner->pa = vec3(0, 19.5, 0);
    cylinder_inner->pb = vec3(0, 0.5, 0);
    cylinder_inner->radius = 11.5;
    cylinder_inner->ior = 1;

    Cylinder *tapa = new Cylinder;
    tapa->color = vec3(1, 0, 0);
    tapa->pa = vec3(0, 22, 0);
    tapa->pb = vec3(0, 20, 0);
    tapa->radius = 8;
    tapa->kd = 0.8;
    tapa->ke = 0.8;

    world.add_object(cylinder_outer);
    world.add_object(cylinder_inner);
    world.add_object(tapa);

    // Firefly 1

    Sphere *fire1 = new Sphere;
    fire1->center = vec3(fire_x, 10, fire_y);
    fire1->color = vec3(1, 1, 0);
    fire1->radius = 0.5;
    fire1->kd = 0.8;
    fire1->ke = 0.8;
    // fire1->ior = 1.5;
    fire1->kr = 8;

    Light *light1 = new Light;
    light1->pos = vec3(0, 10, 0);
    light1->color = vec3(1, 1, 1);

    world.add_object(fire1);
    // world.add_light(light1);

    // Firefly 2

    Sphere *fire2 = new Sphere;
    fire2->center = vec3(-fire_x, 10, -fire_y);
    fire2->color = vec3(1, 1, 0);
    fire2->radius = 0.5;
    fire2->kd = 0.8;
    fire2->ke = 0.8;
    // fire2->ior = 1.5;
    fire2->kr = 8;

    Light *light2 = new Light;
    light2->pos = vec3(4, 10, 0);
    light2->color = vec3(1, 1, 1);

    world.add_object(fire2);
    // world.add_light(light2);

    // External Sphere

    Sphere *sphere1 = new Sphere;
    sphere1->center = vec3(16, 10, 16);
    sphere1->color = vec3(0, 1, 1);
    sphere1->radius = 4;
    sphere1->kd = 0.8;
    sphere1->ke = 0.8;
    sphere1->ks = 8;

    world.add_object(sphere1);

    // External Cylinder

    Cylinder *cylinder1 = new Cylinder;
    cylinder1->color = vec3(1, 0, 0);
    cylinder1->pa = vec3(-20, 10, 10);
    cylinder1->pb = vec3(-20, 0, 10);
    cylinder1->radius = 5;
    cylinder1->kd = 0.8;
    cylinder1->kr = 0.8;

    world.add_object(cylinder1);

    world.render();
}