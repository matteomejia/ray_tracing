#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "vec3.h"

class Object
{
public:
    vec3 color;
    float kd, ke, ks;
    float kr, ior;

    Object()
    {
        kd = 0.5;
        ke = 0;
        ks = 1;
        kr = 0;
        ior = 0;
    }

    virtual bool interseccion(Ray& ray, float& t, vec3& normal) = 0;
};

#endif // OBJECT_H