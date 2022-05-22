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

void escenario()
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

    Camera *camera = new Camera(60, 10, 640, 480, lookfrom, lookat, up);
    camera->calcular_vectores();

    world.add_camera(camera);

    Plane *plane = new Plane();
    plane->n = vec3(1.0f, 10.0f, 1.0f);
    plane->n.normalize();
    plane->d = 0.0f;
    plane->color = vec3(0.5f, 0.5f, 0.5f);
    plane->kd = 0.9f;
    plane->ke = 0.0f;
    plane->kr = 0.5f;

    world.add_object(plane);

    // Luz exterior

    Light *light = new Light;
    light->color = vec3(0.25, 0.25, 0.25);
    light->pos = vec3(100, 100, 100);

    world.add_light(light);

    // Frasco y Tapa

    Cylinder *cylinder_outer = new Cylinder(vec3(0.0f, 20.0f, 0.0f), vec3(0.0f), 12.0f);
    cylinder_outer->ior = 1.0f;
    cylinder_outer->color = vec3(0.25f, 0.25f, 0.25f);

    Cylinder *cylinder_inner = new Cylinder(vec3(0.0f, 19.5f, 0.0f), vec3(0.0f, 0.5f, 0.0f), 11.5f);
    cylinder_inner->ior = 1.0f;
    cylinder_inner->color = vec3(0.25f, 0.25f, 0.25f);

    Cylinder *tapa = new Cylinder(vec3(0.0f, 22.0f, 0.0f), vec3(0.0f, 20.0f, 0.0f), 8.0f);
    tapa->kd = 0.8f;
    tapa->ke = 0.8f;
    tapa->color = vec3(1.0f, 0.0f, 0.0f);

    world.add_object(cylinder_outer);
    world.add_object(cylinder_inner);
    world.add_object(tapa);

    // Firefly 1

    Sphere *fire1 = new Sphere(vec3(fire_x, 10.0f, fire_y), 0.5f);
    fire1->color = vec3(1.0f, 1.0f, 0.0f);
    fire1->kd = 0.8f;
    fire1->ke = 0.8f;
    // fire1->ior = 1.5;
    fire1->kr = 8.0f;

    Light *light1 = new Light;
    light1->pos = vec3(0, 10, 0);
    light1->color = vec3(1, 1, 1);

    world.add_object(fire1);
    // world.add_light(light1);

    // Firefly 2

    Sphere *fire2 = new Sphere(vec3(-fire_x, 10.0f, -fire_y), 0.5f);
    fire2->color = vec3(1.0f, 1.0f, 0.0f);
    fire2->kd = 0.8f;
    fire2->ke = 0.8f;
    // fire2->ior = 1.5;
    fire2->kr = 8.0f;

    Light *light2 = new Light;
    light2->pos = vec3(4, 10, 0);
    light2->color = vec3(1, 1, 1);

    world.add_object(fire2);
    // world.add_light(light2);

    // External Sphere

    Sphere *sphere1 = new Sphere(vec3(16.0f, 10.0f, 16.0f), 4.0f);
    sphere1->color = vec3(0.0f, 1.0f, 1.0f);
    sphere1->kd = 0.8f;
    sphere1->ke = 0.8f;
    sphere1->ks = 8.0f;

    world.add_object(sphere1);

    // External Cylinder

    Cylinder *cylinder1 = new Cylinder(vec3(-20.0f, 10.0f, 10.0f), vec3(-20.0f, 0.0f, 10.0f), 5.0f);
    cylinder1->color = vec3(1.0f, 0.0f, 0.0f);
    cylinder1->kd = 0.8f;
    cylinder1->kr = 0.8f;

    world.add_object(cylinder1);

    world.render();
}

int main(int argc, char **argv)
{
    vec3 lookFrom(50.0f, 20.0f, 10.0f);
    vec3 lookAt(0.0f, 0.0f, 0.0f);
    vec3 up(0.0f, 1.0f, 0.0f);

    Camera camera(60.0f, 10.0f, 800, 600, lookFrom, lookAt, up);
    camera.calcular_vectores();

    std::cout << "xe: " << camera.xe << "\n"
              << "ye: " << camera.ye << "\n"
              << "ze: " << camera.ze << std::endl;

    Sphere *sphere = new Sphere(vec3(0.0f, 0.0f, 0.0f), 4.0f);

    Ray ray;
    ray.direction = vec3(0.0f, 0.0f, 0.0f);
    ray.origin = vec3(40.0f, 40.0f, 40.0f);

    vec3 pi = sphere->get_pi(ray);
    std::cout << pi << std::endl;
}