//
// Created by matte on 8/04/2022.
//

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
    vec3 origin, direction;

    Ray() = default;
    Ray(vec3 ori, vec3 dir)
    {
        origin = ori;
        direction = dir;
    }
};

#endif // RAY_H
