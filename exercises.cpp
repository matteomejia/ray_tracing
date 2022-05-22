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

int main()
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