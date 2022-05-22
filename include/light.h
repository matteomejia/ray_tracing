#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class Light
{
public:
    vec3 pos, color;

    Light() = default;

    Light(vec3 _pos, vec3 _color);

    void set(vec3 _pos, vec3 _color);
};

#endif // LIGHT_H