//
// Created by matte on 8/04/2022.
//

#ifndef RAYTRACING_LIGHT_H
#define RAYTRACING_LIGHT_H

#include "vec3.h"

class Light
{
public:
    vec3 pos, color;

    Light() = default;

    Light(vec3 _pos, vec3 _color)
    {
        pos = _pos;
        color = _color;
    }

    void set(vec3 _pos, vec3 _color)
    {
        pos = _pos;
        color = _color;
    }
};

#endif // RAYTRACING_LIGHT_H
