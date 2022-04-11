//
// Created by matte on 8/04/2022.
//

#ifndef RAYTRACING_WORLD_H
#define RAYTRACING_WORLD_H

#include "camera.h"

class World
{
public:
    Camera cam;
    Light light;
    vector<Object *> objects;

    void init_camera(int angle, float _near, int width, int height, vec3 pos, vec3 cen, vec3 _up)
    {
        cam.fov = angle;
        cam.eye = pos;
        cam.center = cen;
        cam.up = _up;
        cam.f = _near;
        cam.w = width;
        cam.h = height;

        cam.a = 2 * cam.f * tan(cam.fov * 3.141592654 / 360);
        cam.b = cam.a * cam.w / cam.h;

        cam.calcular_vectores();
    }

    void set_light(vec3 pos, vec3 color)
    {
        light.set(pos, color);
    }

    void add_object(Object *obj)
    {
        objects.emplace_back(obj);
    }

    void render()
    {
        cam.render(light, objects);
    }
};

#endif // RAYTRACING_WORLD_H
