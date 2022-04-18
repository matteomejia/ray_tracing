//
// Created by matte on 8/04/2022.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <vector>

#include "cimg.h"
#include "object.h"
#include "light.h"
#include "ray.h"

using namespace cimg_library;
typedef unsigned char BYTE;

class Camera
{
public:
    float fov, f, a, b;
    float w, h;
    vec3 eye, center, up;
    vec3 xe, ye, ze;
    int prof_max;

    CImg<BYTE> *pImg;

    Camera();

    void init(float angle, float _near, int width, int height, vec3 pos, vec3 cen, vec3 _up);

    void calcular_vectores();

    void fresnel(vec3 I, vec3 N, float ior, float &kr);

    vec3 refract(vec3 I, vec3 N, float ior);

    bool calcular_color(Ray ray, std::vector<Light *> lights, std::vector<Object *> &objects, vec3 &color, int prof);

    void render(std::vector<Light *> lights, std::vector<Object *> &objects);
};

#endif // CAMERA_H
