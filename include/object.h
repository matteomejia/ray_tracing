//
// Created by matte on 8/04/2022.
//

#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "vec3.h"

class Object
{
public:
    vec3 color;
    float kd, ke, ks;

    Object()
    {
        kd = 0.5;
        ke = 0;
        ks = 1;
    }

    virtual bool interseccion(Ray &ray, float &t, vec3 &normal) = 0;
};

#endif // OBJECT_H
