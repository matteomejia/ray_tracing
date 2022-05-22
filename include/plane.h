#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "ray.h"
#include "vec3.h"

class Plane : public Object
{
public:
    vec3 n;
    float d;

    Plane() = default;

    bool interseccion(Ray &ray, float &t, vec3 &normal);
};

#endif